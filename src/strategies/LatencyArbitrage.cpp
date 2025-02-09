// latencyarbitrage.cpp
// author: mohammad bazrouk
// implements a latency arbitrage strategy to exploit minor market inefficiencies
#include "LatencyArbitrage.h"
#include <iostream>
#include <chrono>
#include <thread>

namespace hft {
namespace strategies {

latencyarbitrage::latencyarbitrage() : running_(false) {}

latencyarbitrage::~latencyarbitrage() {
    stop();
}

void latencyarbitrage::start() {
    running_ = true;
    worker_ = std::thread([this]() {
        while (running_) {
            // in production, the strategy would continuously monitor for opportunities
            std::this_thread::sleep_for(std::chrono::milliseconds(1));
        }
    });
}

void latencyarbitrage::stop() {
    running_ = false;
    if (worker_.joinable())
        worker_.join();
}

void latencyarbitrage::on_market_data(const marketdatamessage &msg) {
    // evaluate market data for arbitrage opportunity
    std::cout << "latency arbitrage evaluating market data: " << msg.symbol 
              << " price: " << msg.price << std::endl;
    execute_arbitrage(msg);
}

void latencyarbitrage::execute_arbitrage(const marketdatamessage &msg) {
    // dummy execution logic; in production, compare multiple data sources and execution latencies
    std::cout << "executing latency arbitrage on " << msg.symbol << std::endl;
}

} // namespace strategies
} // namespace hft
