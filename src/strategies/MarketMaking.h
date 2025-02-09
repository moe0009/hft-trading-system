// marketmaking.h
// author: mohammad bazrouk
// defines a market making strategy that maintains buy and sell orders
#pragma once

#include "Order.h"
#include "MarketData.h"
#include "OrderRouter.h"
#include <atomic>
#include <thread>

namespace hft {
namespace strategies {

class marketmaking {
public:
    marketmaking();
    ~marketmaking();

    // start the strategy processing
    void start();

    // stop the strategy processing
    void stop();

    // callback for market data messages
    void on_market_data(const marketdatamessage &msg);

private:
    std::atomic<bool> running_;
    std::thread worker_;

    // state for best bid/ask
    double best_bid_;
    double best_ask_;

    // helper function to simulate order placement based on market data
    void place_orders(const marketdatamessage &msg);
};

} // namespace strategies
} // namespace hft
