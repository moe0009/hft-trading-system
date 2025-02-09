// test_orderbook.cpp
// author: mohammad bazrouk
// unit tests for orderbook functionality
#include "core/OrderBook.h"
#include "core/Order.h"
#include <cassert>
#include <iostream>

using namespace hft;

int main() {
    // create orderbook instance
    OrderBook ob;

    // add a buy order
    Order buy_order(1, OrderSide::buy, OrderType::limit, 100, 50.0, 1000);
    bool added_buy = ob.add_order(buy_order);
    assert(added_buy);

    // add a sell order
    Order sell_order(2, OrderSide::sell, OrderType::limit, 100, 50.0, 1001);
    bool added_sell = ob.add_order(sell_order);
    assert(added_sell);

    // create an incoming buy order to match against sell orders
    Order incoming_buy(3, OrderSide::buy, OrderType::limit, 100, 51.0, 1002);
    auto matched_sell = ob.match_order(incoming_buy);
    // expecting one matched order (sell order)
    assert(matched_sell.size() == 1);

    std::cout << "orderbook tests passed" << std::endl;
    return 0;
}
