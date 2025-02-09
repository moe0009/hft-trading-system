// database.cpp
// author: mohammad bazrouk
// implements a simple thread‑safe in‑memory database for persistence.
#include "Database.h"

namespace hft {

database::database() {
    // constructor
}

database::~database() {
    // destructor
}

void database::insert_record(const std::string &table, const std::string &key, const std::string &value) {
    std::lock_guard<std::mutex> lock(mtx_);
    data_[table][key] = value;
}

std::string database::query_record(const std::string &table, const std::string &key) {
    std::lock_guard<std::mutex> lock(mtx_);
    auto tbl_it = data_.find(table);
    if (tbl_it != data_.end()) {
        auto rec_it = tbl_it->second.find(key);
        if (rec_it != tbl_it->second.end()) {
            return rec_it->second;
        }
    }
    return "";
}

} // namespace hft
