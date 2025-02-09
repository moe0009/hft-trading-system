// orderbook.cpp
// author: mohammad bazrouk
// this file implements the lock-free (conceptually) order book.
// note: mutexes are used here for simplicity; in production, replace with lock-free primitives.
#include "OrderBook.h"
#include <algorithm>

namespace hft {

OrderBook::OrderBook() {
    // constructor
}

OrderBook::~OrderBook() {
    // destructor
}

// add order to the order book
bool OrderBook::add_order(const Order &order) {
    std::lock_guard<std::mutex> lock(mtx_);
    // determine side: bid for buy orders, ask for sell orders
    bool is_bid = (order.side == OrderSide::buy);
    bool success = false;
    if (is_bid) {
        success = insert_order(bids_, order, true); // descending order for bids
    } else {
        success = insert_order(asks_, order, false); // ascending order for asks
    }
    return success;
}

// helper function to insert order into given price levels
bool OrderBook::insert_order(std::vector<PriceLevel> &levels, const Order &order, bool descending) {
    // find if a price level already exists
    auto it = std::find_if(levels.begin(), levels.end(), [&](const PriceLevel &pl) {
        return pl.price == order.price;
    });
    if (it == levels.end()) {
        // create new price level if none exists
        PriceLevel pl(order.price);
        pl.orders.push_back(order);
        levels.push_back(pl);
        // sort levels to maintain order
        if (descending) {
            std::sort(levels.begin(), levels.end(), [](const PriceLevel &a, const PriceLevel &b) {
                return a.price > b.price;
            });
        } else {
            std::sort(levels.begin(), levels.end(), [](const PriceLevel &a, const PriceLevel &b) {
                return a.price < b.price;
            });
        }
        // record order location in order_map_
        size_t level_idx = std::distance(levels.begin(), std::find_if(levels.begin(), levels.end(), [&](const PriceLevel &pl) {
            return pl.price == order.price;
        }));
        order_map_[order.id] = { descending, level_idx, 0 };
    } else {
        // append to existing price level (fifo order)
        it->orders.push_back(order);
        size_t level_idx = std::distance(levels.begin(), it);
        size_t order_idx = it->orders.size() - 1;
        order_map_[order.id] = { descending, level_idx, order_idx };
    }
    return true;
}

// cancel an order by id
bool OrderBook::cancel_order(uint64_t order_id) {
    std::lock_guard<std::mutex> lock(mtx_);
    auto it = order_map_.find(order_id);
    if (it == order_map_.end()) {
        return false; // order not found
    }
    OrderLocation loc = it->second;
    std::vector<PriceLevel> &levels = loc.is_bid ? bids_ : asks_;
    if (loc.level_idx >= levels.size()) return false;
    PriceLevel &pl = levels[loc.level_idx];
    if (loc.order_idx >= pl.orders.size()) return false;
    // remove order from the price level
    pl.orders.erase(pl.orders.begin() + loc.order_idx);
    order_map_.erase(it);
    // remove the price level if empty
    if (pl.orders.empty()) {
        levels.erase(levels.begin() + loc.level_idx);
    }
    return true;
}

// match an incoming order against the order book
std::vector<Order> OrderBook::match_order(const Order &incoming) {
    std::lock_guard<std::mutex> lock(mtx_);
    std::vector<Order> matched;
    // for a buy order, match against asks; for a sell order, match against bids
    bool is_bid = (incoming.side == OrderSide::buy);
    std::vector<PriceLevel> &levels = is_bid ? asks_ : bids_;
    // simple matching: for buy order, match orders with price <= incoming.price;
    // for sell order, match orders with price >= incoming.price.
    auto price_cond = [&](double price) -> bool {
        return is_bid ? (price <= incoming.price) : (price >= incoming.price);
    };

    // iterate through price levels to find matches
    for (auto level_it = levels.begin(); level_it != levels.end() && incoming.qty > 0;) {
        if (!price_cond(level_it->price)) {
            break; // no further matching price levels
        }
        // iterate through orders at the price level
        for (auto order_it = level_it->orders.begin(); order_it != level_it->orders.end() && incoming.qty > 0;) {
            // determine matched quantity (simplified: assume full fill)
            uint64_t match_qty = std::min(incoming.qty, order_it->qty);
            Order filled = *order_it;
            filled.qty = match_qty;
            matched.push_back(filled);
            // remove fully filled order
            order_it = level_it->orders.erase(order_it);
            order_map_.erase(filled.id);
        }
        // remove price level if empty
        if (level_it->orders.empty()) {
            level_it = levels.erase(level_it);
        } else {
            ++level_it;
        }
    }
    // note: this simplified matching does not update the incoming order's remaining qty.
    return matched;
}

} // namespace hft
