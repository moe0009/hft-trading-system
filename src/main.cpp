// main.cpp
// author: mohammad bazrouk
// integrates core and infrastructure components to run a simulation of the hft system

#include "core/Order.h"
#include "core/ExecutionEngine.h"
#include "core/Portfolio.h"
#include "core/Market.h"
#include "core/RiskManager.h"
#include "infrastructure/MarketData.h"
#include "infrastructure/OrderRouter.h"
#include "utils/Profiling.h"

#include <iostream>
#include <chrono>
#include <thread>
#include <string>

using namespace hft;

int main() {
    // initialize profiling to measure performance (output in profiling.log)
    hft::profiling::profiler prof("profiling.log");
    prof.mark("start");

    // create portfolio and attach risk manager
    Portfolio portfolio;
    RiskManager risk_manager(&portfolio);

    // start execution engine to process orders
    ExecutionEngine exec_engine;
    exec_engine.start();

    // create market simulation instance for order-driven price updates
    Market market;

    // start market data feed (simulate real-time market data)
    marketdata md;
    md.register_callback([&](const marketdatamessage &msg) {
        // log market data update and update market simulation accordingly
        std::cout << "market data: " << msg.symbol << " @ " << msg.price
                  << " at " << msg.timestamp << std::endl;
        // update market using a dummy order to reflect price impact
        market.update_market(Order(0, OrderSide::buy, OrderType::market, 1, msg.price, msg.timestamp));
    });
    md.start();

    // set up order router for direct market access (simulate exchange connection)
    orderrouter router;
    if (!router.connect("dummy_exchange_endpoint")) {
        std::cerr << "failed to connect to exchange" << std::endl;
        return 1;
    }
    router.register_confirmation_callback([&](const orderconfirmation &conf) {
        std::cout << "order confirmation: id " << conf.order_id
                  << " status: " << (conf.success ? "ok" : "fail")
                  << " message: " << conf.message << std::endl;
    });

    // simulate order submission: create and submit orders in a loop
    for (uint64_t i = 1; i <= 10; ++i) {
        // alternate order side between buy and sell
        Order order(i,
                    (i % 2 == 0 ? OrderSide::buy : OrderSide::sell),
                    OrderType::limit,
                    100,                               // quantity
                    market.current_price(),            // price from current market simulation
                    static_cast<uint64_t>(
                        std::chrono::duration_cast<std::chrono::nanoseconds>(
                            std::chrono::steady_clock::now().time_since_epoch()).count())
        );

        // perform pre-trade risk check
        if (!risk_manager.pre_trade_check(order)) {
            std::cout << "risk check failed for order " << order.id << std::endl;
            continue;
        }

        // submit order to execution engine (for matching and processing)
        exec_engine.submit_order(order);

        // send order to router to simulate exchange connectivity
        router.send_order(order);

        // mark profiling event for order submission
        prof.mark("order submitted " + std::to_string(i));

        // simulate high frequency by sleeping a short duration
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }

    // allow time for orders to process
    std::this_thread::sleep_for(std::chrono::seconds(1));

    // shutdown all components cleanly
    md.stop();
    router.disconnect();
    exec_engine.stop();

    prof.mark("end");
    prof.dump();

    // output final portfolio state for review
    std::cout << "final position: " << portfolio.position()
              << ", pnl: " << portfolio.pnl() << std::endl;

    return 0;
}
