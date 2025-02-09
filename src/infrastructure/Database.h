// database.h
// author: mohammad bazrouk
// provides a simple in‑memory database for trade persistence and market data storage.
#pragma once

#include <string>
#include <unordered_map>
#include <mutex>

namespace hft {

class database {
public:
    database();
    ~database();

    // insert a record into a table
    void insert_record(const std::string &table, const std::string &key, const std::string &value);

    // query a record from a table; returns empty string if not found
    std::string query_record(const std::string &table, const std::string &key);

private:
    // internal storage: table -> (key -> value)
    std::unordered_map<std::string, std::unordered_map<std::string, std::string>> data_;
    mutable std::mutex mtx_;
};

} // namespace hft
