// test_marketdata.cpp
// author: mohammad bazrouk
// unit tests for marketdata module
#include "infrastructure/MarketData.h"
#include <cassert>
#include <iostream>
#include <chrono>
#include <thread>

using namespace hft;

int main() {
    marketdata md;
    bool callback_called = false;

    md.register_callback([&](const marketdatamessage &msg) {
        std::cout << "marketdata callback: " << msg.symbol << " @ " << msg.price << std::endl;
        callback_called = true;
    });

    md.start();
    // allow time for callback invocation
    std::this_thread::sleep_for(std::chrono::milliseconds(50));
    md.stop();

    assert(callback_called);
    std::cout << "marketdata tests passed" << std::endl;
    return 0;
}
