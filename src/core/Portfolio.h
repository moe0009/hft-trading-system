// portfolio.h
// author: mohammad bazrouk
// this file declares the portfolio management module.
// it handles position tracking, pnl updates, and basic risk checks.
#pragma once

#include <atomic>
#include <mutex>
#include "Order.h"

namespace hft {

class Portfolio {
public:
    Portfolio();
    ~Portfolio();

    // update portfolio state based on an executed order and its execution price
    void update_position(const Order &order, double execution_price);

    // return the current net position (positive for net long, negative for net short)
    int64_t position() const;

    // return the current profit and loss
    double pnl() const;

    // perform pre-trade risk check to ensure new order won't exceed limits
    bool risk_check(const Order &order) const;

private:
    std::atomic<int64_t> pos_;    // current net position
    std::atomic<double> pnl_;     // cumulative profit & loss

    // risk limits (could be configurable in production)
    int64_t max_pos_;             // maximum absolute position allowed
    double max_loss_;             // maximum allowable loss (negative pnl)

    mutable std::mutex mtx_;      // mutex to protect updates when necessary
};

} // namespace hft
