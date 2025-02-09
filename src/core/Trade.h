// trade.h
// author: mohammad bazrouk
// defines the trade structure to capture executed trade details for logging, pnl updates, etc.
#pragma once

#include <cstdint>
#include <string>

namespace hft {

struct Trade {
    uint64_t trade_id;     // unique identifier for the trade
    uint64_t buy_order_id; // id of the buy order
    uint64_t sell_order_id;// id of the sell order
    uint64_t qty;          // executed quantity
    double price;          // execution price
    uint64_t timestamp;    // execution timestamp in nanoseconds

    // constructor to initialize trade details
    Trade(uint64_t _trade_id,
          uint64_t _buy_order_id,
          uint64_t _sell_order_id,
          uint64_t _qty,
          double _price,
          uint64_t _timestamp)
        : trade_id(_trade_id),
          buy_order_id(_buy_order_id),
          sell_order_id(_sell_order_id),
          qty(_qty),
          price(_price),
          timestamp(_timestamp)
    {}

    Trade() = default;
};

// helper function to convert a trade to a string for logging or debugging
std::string to_string(const Trade &trade);

} // namespace hft
