// trade.cpp
// author: mohammad bazrouk
// implements helper functions for the trade structure.
#include "Trade.h"
#include <sstream>
#include <iomanip>

namespace hft {

std::string to_string(const Trade &trade) {
    std::ostringstream oss;
    oss << "trade[id:" << trade.trade_id
        << ", buy_order:" << trade.buy_order_id
        << ", sell_order:" << trade.sell_order_id
        << ", qty:" << trade.qty
        << ", price:" << std::fixed << std::setprecision(2) << trade.price
        << ", timestamp:" << trade.timestamp << "]";
    return oss.str();
}

} // namespace hft
