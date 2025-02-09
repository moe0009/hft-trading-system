// latencyarbitrage.h
// author: mohammad bazrouk
// defines a latency arbitrage strategy to exploit sub-microsecond market data discrepancies
#pragma once

#include "Order.h"
#include "MarketData.h"
#include <atomic>
#include <thread>

namespace hft {
namespace strategies {

class latencyarbitrage {
public:
    latencyarbitrage();
    ~latencyarbitrage();

    // start the arbitrage strategy
    void start();

    // stop the strategy
    void stop();

    // callback for market data updates
    void on_market_data(const marketdatamessage &msg);

private:
    std::atomic<bool> running_;
    std::thread worker_;

    // dummy function to simulate arbitrage execution logic
    void execute_arbitrage(const marketdatamessage &msg);
};

} // namespace strategies
} // namespace hft
