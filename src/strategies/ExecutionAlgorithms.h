// executionalgorithms.h
// author: mohammad bazrouk
// defines smart execution algorithms such as vwap, twap, and pov for order execution
#pragma once

#include "Order.h"
#include <vector>

namespace hft {
namespace strategies {

class executionalgorithms {
public:
    executionalgorithms();
    ~executionalgorithms();

    // execute order using vwap algorithm; returns list of sub-orders executed
    std::vector<Order> execute_vwap(const Order &order);

    // execute order using twap algorithm; returns list of sub-orders executed
    std::vector<Order> execute_twap(const Order &order);

    // execute order using pov algorithm; returns list of sub-orders executed
    std::vector<Order> execute_pov(const Order &order);

private:
    // helper to split an order into sub-orders
    std::vector<Order> split_order(const Order &order, uint64_t parts);
};

} // namespace strategies
} // namespace hft
