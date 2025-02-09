# performance tuning

this document outlines performance tuning and profiling guidelines.

## latency optimization

- **lock-free data structures:** replace mutexes with lock-free queues for critical paths.
- **numa-aware allocations:** use the memorymanager to allocate memory aligned with processor cores.
- **thread pinning:** assign worker threads to specific cores to reduce context switching.
- **zero-copy techniques:** minimize data copying, especially in marketdata and orderrouter modules.

## profiling tools

- **profiler module:** use the utils/profiling module to mark events and track execution times.
- **external tools:** integrate flamegraphs, perf, and vtune for deep analysis.
- **benchmarks:** run benchmarks from the benchmarks/ directory to measure throughput and memory bandwidth.

## tuning parameters

- use the config module to adjust critical parameters such as:
  - order batching size
  - thread pool size
  - risk limits and market simulation parameters

continuous profiling and iterative tuning are key to achieving sub-microsecond latency.
