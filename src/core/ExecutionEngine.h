// executionengine.h
// author: mohammad bazrouk

#pragma once

#include "Order.h"
#include "OrderBook.h"
#include <thread>
#include <atomic>
#include <queue>
#include <vector>
#include <mutex>
#include <condition_variable>

namespace hft {

class ExecutionEngine {
public:
    ExecutionEngine();
    ~ExecutionEngine();

    // start the execution engine threads
    void start();

    // stop the execution engine threads
    void stop();

    // submit a new order for execution
    void submit_order(const Order &order);

private:
    // internal order queue; in production, use a lock-free queue
    std::queue<Order> order_q_;
    std::mutex queue_mtx_; 
    std::condition_variable cv_;

    // thread pool for processing orders
    std::vector<std::thread> workers_;
    std::atomic<bool> running_;

    // instance of order book for order matching
    OrderBook order_book_;

    // worker thread function
    void process_orders();
};

} // namespace hft
