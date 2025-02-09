// logger.cpp
// author: mohammad bazrouk
// implements asynchronous logging using a background thread and condition variable.
#include "Logger.h"
#include <fstream>
#include <thread>
#include <mutex>
#include <queue>
#include <condition_variable>
#include <atomic>
#include <iostream>

namespace hft {

class logger::impl {
public:
    impl(const std::string &filename)
        : ofs(filename, std::ios::out | std::ios::app), running(true) {
        worker = std::thread(&impl::process, this);
    }

    ~impl() {
        {
            std::lock_guard<std::mutex> lock(mtx);
            running = false;
        }
        cv.notify_all();
        if (worker.joinable())
            worker.join();
        ofs.close();
    }

    void log(const std::string &level, const std::string &msg) {
        std::lock_guard<std::mutex> lock(mtx);
        queue.push("[" + level + "] " + msg);
        cv.notify_one();
    }

    void flush() {
        std::lock_guard<std::mutex> lock(mtx);
        while (!queue.empty()) {
            ofs << queue.front() << "\n";
            queue.pop();
        }
        ofs.flush();
    }

private:
    void process() {
        while (running) {
            std::unique_lock<std::mutex> lock(mtx);
            cv.wait(lock, [this] { return !queue.empty() || !running; });
            while (!queue.empty()) {
                ofs << queue.front() << "\n";
                queue.pop();
            }
            ofs.flush();
        }
    }

    std::ofstream ofs;
    std::queue<std::string> queue;
    std::mutex mtx;
    std::condition_variable cv;
    std::atomic<bool> running;
    std::thread worker;
};

logger::logger(const std::string &filename) : pimpl_(new impl(filename)) {}

logger::~logger() {
    delete pimpl_;
}

void logger::log(const std::string &level, const std::string &msg) {
    pimpl_->log(level, msg);
}

void logger::flush() {
    pimpl_->flush();
}

} // namespace hft
