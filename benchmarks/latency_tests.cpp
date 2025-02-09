// latency_tests.cpp
// author: mohammad bazrouk
// benchmarks latency by measuring time differences over many iterations
#include <chrono>
#include <iostream>
#include <vector>

using namespace std::chrono;

int main() {
    const int iterations = 1000000;
    std::vector<long long> latencies;
    latencies.reserve(iterations);

    for (int i = 0; i < iterations; ++i) {
        auto start = steady_clock::now();
        // simulate minimal work
        auto end = steady_clock::now();
        auto duration = duration_cast<nanoseconds>(end - start).count();
        latencies.push_back(duration);
    }

    // compute average latency
    long long total = 0;
    for (auto l : latencies) total += l;
    double avg = static_cast<double>(total) / iterations;
    std::cout << "average latency: " << avg << " ns over " << iterations << " iterations" << std::endl;
    return 0;
}
