// marketdata.cpp
// author: mohammad bazrouk
// implements market data feed handling with zero-copy parsing where applicable.
#include "MarketData.h"
#include <chrono>
#include <cstdlib>
#include <iostream>

namespace hft {

marketdata::marketdata() : running_(false) {
    // initialize market data feed state
}

marketdata::~marketdata() {
    stop();
}

void marketdata::start() {
    running_ = true;
    feed_thread_ = std::thread(&marketdata::process_feed, this);
}

void marketdata::stop() {
    running_ = false;
    if (feed_thread_.joinable()) {
        feed_thread_.join();
    }
}

void marketdata::register_callback(callback_t cb) {
    std::lock_guard<std::mutex> lock(cb_mtx_);
    callback_ = cb;
}

void marketdata::process_feed() {
    // simulate receiving market data messages in real-time
    while (running_) {
        marketdatamessage msg;
        // simulate raw feed parsing; in production, apply zero-copy techniques
        msg.symbol = "aapl";
        msg.price = 150.0 + (std::rand() % 1000) / 100.0;
        msg.timestamp = static_cast<uint64_t>(
            std::chrono::duration_cast<std::chrono::nanoseconds>(
                std::chrono::steady_clock::now().time_since_epoch()).count());

        {
            std::lock_guard<std::mutex> lock(cb_mtx_);
            if (callback_) {
                callback_(msg);
            }
        }
        // simulate a high-frequency feed; in production this is event driven
        std::this_thread::sleep_for(std::chrono::milliseconds(1));
    }
}

} // namespace hft
