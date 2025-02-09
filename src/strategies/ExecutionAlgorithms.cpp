// executionalgorithms.cpp
// author: mohammad bazrouk
// implements smart execution algorithms for order splitting (vwap, twap, pov)
#include "ExecutionAlgorithms.h"
#include <iostream>

namespace hft {
namespace strategies {

executionalgorithms::executionalgorithms() {}

executionalgorithms::~executionalgorithms() {}

std::vector<Order> executionalgorithms::split_order(const Order &order, uint64_t parts) {
    std::vector<Order> sub_orders;
    if (parts == 0) return sub_orders;
    uint64_t qty_per_part = order.qty / parts;
    uint64_t remaining = order.qty % parts;
    uint64_t base_id = order.id;
    for (uint64_t i = 0; i < parts; ++i) {
        uint64_t qty = qty_per_part + (i < remaining ? 1 : 0);
        // generate a new sub-order id; in production, ensure uniqueness properly
        Order sub_order(base_id * 100 + i, order.side, order.type, qty, order.price, order.timestamp);
        sub_orders.push_back(sub_order);
    }
    return sub_orders;
}

std::vector<Order> executionalgorithms::execute_vwap(const Order &order) {
    uint64_t parts = 5; // dummy split count; production would use market volume data
    std::cout << "executing vwap for order " << order.id << std::endl;
    return split_order(order, parts);
}

std::vector<Order> executionalgorithms::execute_twap(const Order &order) {
    uint64_t parts = 10; // dummy split count for twap
    std::cout << "executing twap for order " << order.id << std::endl;
    return split_order(order, parts);
}

std::vector<Order> executionalgorithms::execute_pov(const Order &order) {
    uint64_t parts = 7; // dummy split count for pov
    std::cout << "executing pov for order " << order.id << std::endl;
    return split_order(order, parts);
}

} // namespace strategies
} // namespace hft
