// networking.h
// author: mohammad bazrouk
// provides a basic abstraction for ultra‑low latency networking.
// in production, this would integrate kernel‑bypass techniques (dpdk/rdma) for minimal latency.
#pragma once

#include <string>

namespace hft {

class networking {
public:
    networking();
    ~networking();

    // connect to a remote endpoint
    bool connect(const std::string &endpoint);

    // disconnect from the remote endpoint
    void disconnect();

    // send raw data; returns true if sent successfully
    bool send_data(const char *data, size_t len);

    // receive raw data into buffer; returns number of bytes received or -1 on error
    int receive_data(char *buffer, size_t len);

private:
    bool connected_; // connection state; true if connected
    // in production, socket descriptors or dpdk context handles would be stored here
};

} // namespace hft
