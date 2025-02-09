// marketdata.h
// author: mohammad bazrouk
// this module handles real-time market data feeds.
// it supports feed connections (e.g., itch, websockets) and processes raw market messages.
#pragma once

#include <functional>
#include <thread>
#include <atomic>
#include <mutex>
#include <condition_variable>
#include <string>

namespace hft {

struct marketdatamessage {
    std::string symbol;
    double price;
    uint64_t timestamp;
};

class marketdata {
public:
    using callback_t = std::function<void(const marketdatamessage&)>;

    marketdata();
    ~marketdata();

    // start market data feed processing
    void start();

    // stop market data feed processing
    void stop();

    // register a callback to receive market data messages
    void register_callback(callback_t cb);

private:
    // internal thread function to simulate or process market feed data
    void process_feed();

    std::atomic<bool> running_;
    std::thread feed_thread_;
    callback_t callback_;
    mutable std::mutex cb_mtx_;
};

} // namespace hft
