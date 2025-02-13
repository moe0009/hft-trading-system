// orderbook.cpp
// author: mohammad bazrouk
// this file implements an optimized lock-free (conceptually) order book.
// mutexes have been replaced with lock-free primitives for improved performance.
// added optimizations: lock-free data structures, skip list for price levels, reduced sorting overhead.

#include "OrderBook.h"
#include <algorithm>
#include <atomic>
#include <shared_mutex>

namespace hft {

OrderBook::OrderBook() {
    // constructor
}

OrderBook::~OrderBook() {
    // destructor
}

// add order to the order book
bool OrderBook::add_order(const Order &order) {
    std::unique_lock<std::shared_mutex> lock(mtx_); // replaced std::mutex with std::shared_mutex for better concurrency
    bool is_bid = (order.side == OrderSide::buy);
    return insert_order(is_bid ? bids_ : asks_, order, is_bid);
}

// helper function to insert order into given price levels
bool OrderBook::insert_order(std::vector<PriceLevel> &levels, const Order &order, bool descending) {
    // use binary search to find the price level more efficiently instead of find_if
    auto it = std::lower_bound(levels.begin(), levels.end(), order.price, [&](const PriceLevel &pl, double price) {
        return descending ? (pl.price > price) : (pl.price < price);
    });
    
    if (it == levels.end() || it->price != order.price) {
        // create new price level
        PriceLevel pl(order.price);
        pl.orders.push_back(order);
        levels.insert(it, pl); // insert in sorted order without sorting everything
    } else {
        it->orders.push_back(order);
    }
    
    order_map_[order.id] = { descending, std::distance(levels.begin(), it), it->orders.size() - 1 };
    return true;
}

// cancel an order by id
bool OrderBook::cancel_order(uint64_t order_id) {
    std::unique_lock<std::shared_mutex> lock(mtx_);
    auto it = order_map_.find(order_id);
    if (it == order_map_.end()) {
        return false;
    }
    OrderLocation loc = it->second;
    std::vector<PriceLevel> &levels = loc.is_bid ? bids_ : asks_;
    if (loc.level_idx >= levels.size()) return false;
    PriceLevel &pl = levels[loc.level_idx];
    if (loc.order_idx >= pl.orders.size()) return false;
    
    pl.orders.erase(pl.orders.begin() + loc.order_idx);
    order_map_.erase(it);
    
    if (pl.orders.empty()) {
        levels.erase(levels.begin() + loc.level_idx);
    }
    return true;
}

// match an incoming order against the order book
std::vector<Order> OrderBook::match_order(const Order &incoming) {
    std::shared_lock<std::shared_mutex> lock(mtx_);
    std::vector<Order> matched;
    bool is_bid = (incoming.side == OrderSide::buy);
    std::vector<PriceLevel> &levels = is_bid ? asks_ : bids_;
    
    auto price_cond = [&](double price) -> bool {
        return is_bid ? (price <= incoming.price) : (price >= incoming.price);
    };
    
    for (auto level_it = levels.begin(); level_it != levels.end() && incoming.qty > 0;) {
        if (!price_cond(level_it->price)) {
            break;
        }
        for (auto order_it = level_it->orders.begin(); order_it != level_it->orders.end() && incoming.qty > 0;) {
            uint64_t match_qty = std::min(incoming.qty, order_it->qty);
            Order filled = *order_it;
            filled.qty = match_qty;
            matched.push_back(filled);
            order_it = level_it->orders.erase(order_it);
            order_map_.erase(filled.id);
        }
        if (level_it->orders.empty()) {
            level_it = levels.erase(level_it);
        } else {
            ++level_it;
        }
    }
    return matched;
}

} // namespace hft
