// market.h
// author: mohammad bazrouk
// this module simulates market price dynamics based on order flow.
// in a production system, this would be replaced by real-time market data.
#pragma once

namespace hft {

class Market {
public:
    Market();
    ~Market();

    // update market price based on incoming order characteristics
    void update_market(const Order &order);

    // retrieve the current market price
    double current_price() const;

private:
    double price_;  // current market price
};

} // namespace hft
