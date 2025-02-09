// orderrouter.cpp
// author: mohammad bazrouk
// implements the order router for direct market access and smart order routing.
#include "OrderRouter.h"
#include <chrono>
#include <iostream>

namespace hft {

orderrouter::orderrouter() : running_(false), connected_(false) {
    // initialize order router state
}

orderrouter::~orderrouter() {
    disconnect();
}

bool orderrouter::connect(const std::string &exchange_endpoint) {
    std::lock_guard<std::mutex> lock(conn_mtx_);
    // simulate connecting to an exchange; in production, perform proper network initialization
    connected_ = true;
    running_ = true;
    response_thread_ = std::thread(&orderrouter::process_responses, this);
    return connected_;
}

void orderrouter::disconnect() {
    {
        std::lock_guard<std::mutex> lock(conn_mtx_);
        if (!connected_) {
            return;
        }
        connected_ = false;
    }
    running_ = false;
    if (response_thread_.joinable()) {
        response_thread_.join();
    }
}

void orderrouter::send_order(const Order &order) {
    // in production, serialize the order and send via dma or fix protocols
    // here, we simulate immediate processing and confirmation
    orderconfirmation conf;
    conf.order_id = order.id;
    conf.success = true;
    conf.message = "order routed successfully";
    // simulate network latency
    std::this_thread::sleep_for(std::chrono::microseconds(50));
    {
        std::lock_guard<std::mutex> lock(cb_mtx_);
        if (confirm_cb_) {
            confirm_cb_(conf);
        }
    }
}

void orderrouter::register_confirmation_callback(confirmation_callback_t cb) {
    std::lock_guard<std::mutex> lock(cb_mtx_);
    confirm_cb_ = cb;
}

void orderrouter::process_responses() {
    // in production, this thread would listen for responses from the exchange.
    // here, we simulate periodic tasks or keep-alive messages.
    while (running_) {
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }
}

} // namespace hft
