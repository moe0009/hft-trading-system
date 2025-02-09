// marketmaking.cpp
// author: mohammad bazrouk
// implements a simple market making strategy that places buy and sell orders based on market data
#include "MarketMaking.h"
#include <iostream>
#include <chrono>
#include <thread>

namespace hft {
namespace strategies {

marketmaking::marketmaking() : running_(false), best_bid_(0.0), best_ask_(0.0) {}

marketmaking::~marketmaking() {
    stop();
}

void marketmaking::start() {
    running_ = true;
    // in production, this would be event driven; here we simulate periodic processing
    worker_ = std::thread([this]() {
        while (running_) {
            std::this_thread::sleep_for(std::chrono::milliseconds(50));
            // periodic tasks or heartbeat could go here
            std::cout << "market making strategy running" << std::endl;
        }
    });
}

void marketmaking::stop() {
    running_ = false;
    if (worker_.joinable())
        worker_.join();
}

void marketmaking::on_market_data(const marketdatamessage &msg) {
    // update best bid/ask based on received market price (simulate a fixed spread)
    double spread = 0.05;
    best_bid_ = msg.price - spread / 2.0;
    best_ask_ = msg.price + spread / 2.0;
    std::cout << "market data received: " << msg.symbol << " price: " << msg.price
              << ", best_bid: " << best_bid_ << ", best_ask: " << best_ask_ << std::endl;
    place_orders(msg);
}

void marketmaking::place_orders(const marketdatamessage &msg) {
    // in production, orders would be routed via the execution engine/order router
    static uint64_t order_id = 1000;
    Order buy_order(order_id++, OrderSide::buy, OrderType::limit, 100, best_bid_, msg.timestamp);
    Order sell_order(order_id++, OrderSide::sell, OrderType::limit, 100, best_ask_, msg.timestamp);
    std::cout << "placing market making orders: " << to_string(buy_order)
              << " | " << to_string(sell_order) << std::endl;
}

} // namespace strategies
} // namespace hft
