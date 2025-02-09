// order.h
// author: mohammad bazrouk
#pragma once

#include <cstdint>
#include <string>

namespace hft {

enum class OrderType : uint8_t {
    market,     // market order
    limit,      // limit order
    iceberg,    // iceberg order with hidden quantity
    hidden,     // completely hidden order
    pegged,     // pegged order to best bid/ask
    post_only   // post-only order
};

enum class OrderSide : uint8_t {
    buy,  // buy order
    sell  // sell order
};

struct Order {
    uint64_t id;           // unique order identifier
    OrderSide side;        // buy or sell
    OrderType type;        // order type (market, limit, etc.)
    uint64_t qty;          // total quantity of order
    double price;          // limit price, if applicable
    uint64_t timestamp;    // order entry time in nanoseconds

    // iceberg order specific field
    uint64_t peak_qty;     // visible qty for iceberg orders

    // pegged order specific field
    double pegged_offset;  // offset from best bid/ask for pegged orders

    // constructor for complete order creation
    Order(uint64_t _id, OrderSide _side, OrderType _type, uint64_t _qty,
          double _price, uint64_t _timestamp,
          uint64_t _peak_qty = 0, double _pegged_offset = 0.0)
        : id(_id), side(_side), type(_type), qty(_qty),
          price(_price), timestamp(_timestamp),
          peak_qty(_peak_qty), pegged_offset(_pegged_offset) {}

    Order() = default; // default constructor
};

// helper function to convert an order to string for logging/debugging
std::string to_string(const Order &order);

} // namespace hft
