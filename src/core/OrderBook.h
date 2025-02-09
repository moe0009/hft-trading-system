// orderbook.h
// author: mohammad bazrouk
// this file defines a lock-free, numa-aware order book for the hft system.
// note: for simplicity, this implementation uses mutexes as placeholders for lock-free primitives.
#pragma once

#include "Order.h"
#include <cstdint>
#include <atomic>
#include <vector>
#include <unordered_map>
#include <mutex>
#include <memory>

namespace hft {

class OrderBook {
public:
    OrderBook();
    ~OrderBook();

    // add a new order to the book, returns true if added successfully
    bool add_order(const Order &order);

    // cancel an existing order by id, returns true if cancelled
    bool cancel_order(uint64_t order_id);

    // match an incoming order against the book and return matched orders
    // note: this is a simplified matching interface.
    std::vector<Order> match_order(const Order &incoming);

private:
    // internal representation for orders at a given price level
    struct PriceLevel {
        double price;             // price level
        std::vector<Order> orders; // orders at this price level in fifo order

        PriceLevel(double p) : price(p) {}
    };

    // separate order books for bids and asks
    std::vector<PriceLevel> bids_; // bids sorted in descending order
    std::vector<PriceLevel> asks_; // asks sorted in ascending order

    // order lookup for cancellations: maps order id to its location
    struct OrderLocation {
        bool is_bid;       // true if order is in bids
        size_t level_idx;  // index in bids_ or asks_
        size_t order_idx;  // index within the orders vector at that price level
    };
    std::unordered_map<uint64_t, OrderLocation> order_map_;

    // mutex to protect order book data (replace with lock-free primitives in production)
    mutable std::mutex mtx_;

    // helper function to insert an order into a price level vector
    bool insert_order(std::vector<PriceLevel> &levels, const Order &order, bool descending);
};

} // namespace hft
