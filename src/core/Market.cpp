// market.cpp
// author: mohammad bazrouk
// implements a simple order-driven market simulation.
// note: this is a simplified model; real market impact models are more complex.
#include "Market.h"
#include "Order.h"
#include <algorithm>

namespace hft {

Market::Market() : price_(100.0) { // initialize with a base price
}

Market::~Market() {}

void Market::update_market(const Order &order) {
    // simulate price impact: impact proportional to order size relative to liquidity
    // in production, liquidity would be dynamic and multi-dimensional.
    const double liquidity = 1000000.0;  
    double impact = static_cast<double>(order.qty) / liquidity;
    if (order.side == OrderSide::buy) {
        price_ += impact;
    } else {
        price_ -= impact;
    }
    // ensure the price remains within realistic bounds
    price_ = std::max(price_, 1.0);
}

double Market::current_price() const {
    return price_;
}

} // namespace hft
