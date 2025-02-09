// profiling.cpp
// author: mohammad bazrouk
// implements advanced profiling for latency and performance measurement.
#include "Profiling.h"
#include <chrono>

namespace hft {
namespace profiling {

profiler::profiler(const std::string &filename) {
    ofs_.open(filename, std::ios::out | std::ios::trunc);
}

profiler::~profiler() {
    if (ofs_.is_open()) {
        dump();
        ofs_.close();
    }
}

void profiler::mark(const std::string &label) {
    // record the current time in microseconds along with the event label
    auto now = std::chrono::steady_clock::now();
    ofs_ << label << " : " 
         << std::chrono::duration_cast<std::chrono::microseconds>(now.time_since_epoch()).count()
         << "us\n";
}

void profiler::dump() {
    // flush the profiling data; in production, use structured output for analysis
    ofs_.flush();
}

} // namespace profiling
} // namespace hft
