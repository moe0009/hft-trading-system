// riskmanager.h
// author: mohammad bazrouk
// declares the risk manager module which enforces pre-trade checks and updates risk post-trade.
#pragma once

#include "Order.h"

namespace hft {

// forward declaration for portfolio
class Portfolio;

class RiskManager {
public:
    RiskManager(Portfolio *portfolio);
    ~RiskManager();

    // perform pre-trade risk checks, return true if order passes risk parameters
    bool pre_trade_check(const Order &order) const;

    // update risk parameters after a trade is executed
    void update_after_trade(const Order &order, double exec_price);

private:
    Portfolio *portfolio_;  // pointer to the portfolio module for risk aggregation
};

} // namespace hft
