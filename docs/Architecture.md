# system architecture

this document details the architecture of the hft trading system.

## overview

the system is organized into several layers:

- **core:** contains trading logic including order management, matching, execution, risk, portfolio, market simulation, and trade capture.
- **infrastructure:** handles connectivity such as market data ingestion, order routing, networking, logging, and database persistence.
- **strategies:** houses various trading strategies (market making, execution algorithms, latency arbitrage).
- **utils:** provides configuration management, advanced profiling, and memory management tools.

## design principles

- **modularity:** each module is independent, allowing easy testing and rapid development.
- **performance-first:** the system uses lock-free techniques, multi-threading, and numa-aware optimizations to achieve ultra-low latency.
- **scalability:** components are designed to run on multi-core servers with potential for kernel bypass networking.
- **testability:** unit tests and benchmarks ensure reliability under high load.

## data flow

1. market data arrives via the marketdata module.
2. strategies process the data and generate orders.
3. orders are submitted to the execution engine, which interacts with the order book.
4. trade executions update the portfolio and risk manager.
5. orderrouter handles external connectivity to exchanges.
6. logging and profiling record performance metrics.
