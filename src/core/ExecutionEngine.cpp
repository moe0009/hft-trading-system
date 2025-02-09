// executionengine.cpp
// author: mohammad bazrouk

#include "ExecutionEngine.h"
#include <chrono>
#include <algorithm>

namespace hft {

ExecutionEngine::ExecutionEngine() : running_(false) {
    // constructor
}

ExecutionEngine::~ExecutionEngine() {
    stop();
}

// start the execution engine threads
void ExecutionEngine::start() {
    running_ = true;
    // spawn worker threads; in production, thread pinning and numa-aware allocation is recommended
    size_t num_threads = std::thread::hardware_concurrency();
    for (size_t i = 0; i < num_threads; ++i) {
        workers_.emplace_back(&ExecutionEngine::process_orders, this);
    }
}

// stop the execution engine threads
void ExecutionEngine::stop() {
    running_ = false;
    cv_.notify_all();
    for (auto &worker : workers_) {
        if (worker.joinable()) {
            worker.join();
        }
    }
    workers_.clear();
}

// submit a new order for execution
void ExecutionEngine::submit_order(const Order &order) {
    {
        std::lock_guard<std::mutex> lock(queue_mtx_);
        order_q_.push(order);
    }
    cv_.notify_one();
}

// worker thread function to process orders
void ExecutionEngine::process_orders() {
    while (running_) {
        Order order;
        {
            std::unique_lock<std::mutex> lock(queue_mtx_);
            cv_.wait(lock, [this]() { return !order_q_.empty() || !running_; });
            if (!running_ && order_q_.empty()) {
                return;
            }
            order = order_q_.front();
            order_q_.pop();
        }
        // process order by matching it in the order book
        // note: in production, use zero-copy techniques and lock-free queues for ultra-low latency
        auto matched = order_book_.match_order(order);
        // in a full implementation, trade events would be published here;
        // minimal logging or processing should be done inline in production systems.
    }
}

} // namespace hft
