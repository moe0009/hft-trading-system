// logger.h
// author: mohammad bazrouk
// provides asynchronous logging with minimal impact on trading performance.
#pragma once

#include <string>

namespace hft {

class logger {
public:
    logger(const std::string &filename);
    ~logger();

    // log a message with a specified level (info, error, debug, etc.)
    void log(const std::string &level, const std::string &msg);

    // flush log messages to file
    void flush();

private:
    // disable copying
    logger(const logger &) = delete;
    logger &operator=(const logger &) = delete;

    // pimpl idiom for implementation hiding and easier optimization
    class impl;
    impl *pimpl_;
};

} // namespace hft
