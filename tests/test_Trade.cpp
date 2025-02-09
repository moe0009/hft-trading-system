// test_trade.cpp
// author: mohammad bazrouk
// unit tests for trade module
#include "core/Trade.h"
#include <cassert>
#include <iostream>

using namespace hft;

int main() {
    Trade t(1, 10, 20, 100, 55.0, 123456789);
    std::string t_str = to_string(t);
    std::cout << t_str << std::endl;
    assert(!t_str.empty());
    std::cout << "trade tests passed" << std::endl;
    return 0;
}
