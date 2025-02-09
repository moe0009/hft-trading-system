// test_executionengine.cpp
// author: mohammad bazrouk
// unit tests for execution engine functionality
#include "core/ExecutionEngine.h"
#include "core/Order.h"
#include <cassert>
#include <iostream>
#include <chrono>
#include <thread>

using namespace hft;

int main() {
    ExecutionEngine engine;
    engine.start();

    // submit a series of orders
    for (uint64_t i = 10; i < 20; ++i) {
        Order order(i, (i % 2 == 0 ? OrderSide::buy : OrderSide::sell),
                    OrderType::limit, 50, 100.0 + (i % 5), 1000 + i);
        engine.submit_order(order);
    }

    // allow some time for processing
    std::this_thread::sleep_for(std::chrono::milliseconds(200));

    engine.stop();
    std::cout << "execution engine tests passed" << std::endl;
    return 0;
}
