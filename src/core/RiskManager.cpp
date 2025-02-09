// riskmanager.cpp
// author: mohammad bazrouk
// implements risk management by interfacing with portfolio risk limits.
#include "RiskManager.h"
#include "Portfolio.h"

namespace hft {

RiskManager::RiskManager(Portfolio *portfolio)
    : portfolio_(portfolio)
{}

RiskManager::~RiskManager() {}

bool RiskManager::pre_trade_check(const Order &order) const {
    // delegate risk check to the portfolio module
    return portfolio_->risk_check(order);
}

void RiskManager::update_after_trade(const Order &order, double exec_price) {
    // update portfolio after order execution for risk aggregation
    portfolio_->update_position(order, exec_price);
}

} // namespace hft
