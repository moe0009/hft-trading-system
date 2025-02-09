// profiling.h
// author: mohammad bazrouk
// this module provides advanced latency tracking and profiling tools for performance analysis.
#pragma once

#include <chrono>
#include <string>
#include <fstream>

namespace hft {
namespace profiling {

class profiler {
public:
    profiler(const std::string &filename);
    ~profiler();

    // mark a timestamp for a given event label
    void mark(const std::string &label);

    // dump profiling results to file
    void dump();

private:
    std::ofstream ofs_;
    // in production, use high-resolution timers and lock-free data structures for event recording.
};

} // namespace profiling
} // namespace hft
