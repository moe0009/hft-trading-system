// memory_bandwidth_tests.cpp
// author: mohammad bazrouk
// benchmarks memory bandwidth by measuring memcpy throughput
#include <chrono>
#include <cstring>
#include <iostream>
#include <vector>

using namespace std::chrono;

int main() {
    const size_t buffer_size = 100 * 1024 * 1024; // 100 mb
    std::vector<char> src(buffer_size, 'a');
    std::vector<char> dst(buffer_size, 0);

    auto start = steady_clock::now();
    std::memcpy(dst.data(), src.data(), buffer_size);
    auto end = steady_clock::now();

    auto duration = duration_cast<milliseconds>(end - start).count();
    double bandwidth = (buffer_size / (1024.0 * 1024.0)) / (duration / 1000.0);
    std::cout << "memory copy bandwidth: " << bandwidth << " mb/s" << std::endl;
    return 0;
}
