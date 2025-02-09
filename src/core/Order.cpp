// order.cpp
// author: mohammad bazrouk
#include "Order.h"
#include <sstream>
#include <iomanip>

namespace hft {

std::string to_string(const Order &order) {
    std::ostringstream oss;
    oss << "order[id:" << order.id
        << ", side:" << (order.side == OrderSide::buy ? "buy" : "sell")
        << ", type:";
    switch(order.type) {
        case OrderType::market:     oss << "market"; break;
        case OrderType::limit:      oss << "limit"; break;
        case OrderType::iceberg:    oss << "iceberg"; break;
        case OrderType::hidden:     oss << "hidden"; break;
        case OrderType::pegged:     oss << "pegged"; break;
        case OrderType::post_only:  oss << "post_only"; break;
        default:                    oss << "unknown"; break;
    }
    oss << ", qty:" << order.qty
        << ", price:" << std::fixed << std::setprecision(2) << order.price
        << ", timestamp:" << order.timestamp;
    if (order.type == OrderType::iceberg) {
        oss << ", peak_qty:" << order.peak_qty;
    }
    if (order.type == OrderType::pegged) {
        oss << ", pegged_offset:" << order.pegged_offset;
    }
    oss << "]";
    return oss.str();
}

}
