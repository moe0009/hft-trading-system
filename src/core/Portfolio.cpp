// portfolio.cpp
// author: mohammad bazrouk
// implements the portfolio management functions for real-time pnl and risk updates.
#include "Portfolio.h"
#include <cmath>

namespace hft {

Portfolio::Portfolio()
    : pos_(0),
      pnl_(0.0),
      max_pos_(1000000),     // example limit: 1m units
      max_loss_(-100000.0)   // example risk limit: max loss of 100k
{}

Portfolio::~Portfolio() {}

void Portfolio::update_position(const Order &order, double exec_price) {
    // acquire lock for precise portfolio update
    std::lock_guard<std::mutex> lock(mtx_);
    int64_t qty = static_cast<int64_t>(order.qty);
    // update position and pnl based on order side
    if (order.side == OrderSide::buy) {
        pos_ += qty;
        pnl_ -= qty * exec_price;
    } else {
        pos_ -= qty;
        pnl_ += qty * exec_price;
    }
}

int64_t Portfolio::position() const {
    return pos_.load(std::memory_order_relaxed);
}

double Portfolio::pnl() const {
    return pnl_.load(std::memory_order_relaxed);
}

bool Portfolio::risk_check(const Order &order) const {
    // simulate the position after order execution
    int64_t new_pos = position();
    int64_t qty = static_cast<int64_t>(order.qty);
    new_pos += (order.side == OrderSide::buy) ? qty : -qty;

    // check if new position exceeds limit
    if (std::abs(new_pos) > max_pos_) {
        return false;
    }
    // additional risk logic (e.g., pnl thresholds) can be added here
    return true;
}

} // namespace hft
