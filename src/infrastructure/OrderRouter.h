// orderrouter.h
// author: mohammad bazrouk
// this module handles direct market access and smart order routing.
// it supports connections to exchanges via protocols like fix and dma.
#pragma once

#include "Order.h"
#include <functional>
#include <thread>
#include <atomic>
#include <mutex>
#include <condition_variable>
#include <string>

namespace hft {

struct orderconfirmation {
    uint64_t order_id;
    bool success;
    std::string message;
};

class orderrouter {
public:
    using confirmation_callback_t = std::function<void(const orderconfirmation&)>;

    orderrouter();
    ~orderrouter();

    // connect to the exchange or a simulated exchange endpoint
    bool connect(const std::string &exchange_endpoint);

    // disconnect from the exchange
    void disconnect();

    // send an order to the exchange
    void send_order(const Order &order);

    // register a callback to receive order confirmations
    void register_confirmation_callback(confirmation_callback_t cb);

private:
    // internal thread function to simulate exchange responses
    void process_responses();

    std::atomic<bool> running_;
    std::thread response_thread_;
    confirmation_callback_t confirm_cb_;
    mutable std::mutex cb_mtx_;

    // dummy connection state
    bool connected_;
    mutable std::mutex conn_mtx_;
};

} // namespace hft
