// order_throughput_tests.cpp
// author: mohammad bazrouk
// benchmarks order throughput by submitting many orders to the execution engine
#include "core/ExecutionEngine.h"
#include "core/Order.h"
#include <chrono>
#include <iostream>
#include <thread>

using namespace hft;
using namespace std::chrono;

int main() {
    ExecutionEngine engine;
    engine.start();

    const int total_orders = 100000;
    auto start = steady_clock::now();

    for (int i = 0; i < total_orders; ++i) {
        Order order(i, (i % 2 == 0 ? OrderSide::buy : OrderSide::sell),
                    OrderType::limit, 10, 100.0, 1000 + i);
        engine.submit_order(order);
    }

    // wait for orders to process
    std::this_thread::sleep_for(milliseconds(500));
    auto end = steady_clock::now();
    engine.stop();

    auto duration = duration_cast<milliseconds>(end - start).count();
    std::cout << "submitted " << total_orders << " orders in " << duration << " ms" << std::endl;
    std::cout << "throughput: " << (total_orders * 1000.0 / duration)
              << " orders per second" << std::endl;
    return 0;
}
