// networking.cpp
// author: mohammad bazrouk
// implements basic networking functions.
// in a real hft system, replace this with dpdk/rdma‑based implementations.
#include "Networking.h"
#include <iostream>
#include <cstring>

namespace hft {

networking::networking() : connected_(false) {
    // initialize networking resources
}

networking::~networking() {
    if (connected_) {
        disconnect();
    }
}

bool networking::connect(const std::string &endpoint) {
    // simulate connection establishment
    std::cout << "connecting to " << endpoint << std::endl;
    connected_ = true; // in production, check for errors
    return connected_;
}

void networking::disconnect() {
    if (connected_) {
        // simulate disconnecting
        std::cout << "disconnecting from network" << std::endl;
        connected_ = false;
    }
}

bool networking::send_data(const char *data, size_t len) {
    if (!connected_) return false;
    // simulate sending data over network
    std::cout << "sending data: " << std::string(data, len) << std::endl;
    return true;
}

int networking::receive_data(char *buffer, size_t len) {
    if (!connected_) return -1;
    // simulate receiving data; in production, use non‑blocking io
    const char *dummy = "response";
    size_t dummy_len = std::strlen(dummy);
    size_t copy_len = (dummy_len < len) ? dummy_len : len;
    std::memcpy(buffer, dummy, copy_len);
    return static_cast<int>(copy_len);
}

} // namespace hft
