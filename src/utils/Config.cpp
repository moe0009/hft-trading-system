// config.cpp
// author: mohammad bazrouk
// implements configuration file parsing and parameter access.
#include "Config.h"
#include <fstream>
#include <sstream>

namespace hft {
namespace config {

config::config() {}

config::~config() {}

bool config::load(const std::string &filename) {
    std::ifstream ifs(filename);
    if (!ifs.is_open()) return false;
    std::string line;
    while (std::getline(ifs, line)) {
        // ignore comments and empty lines
        if (line.empty() || line[0] == '#') continue;
        std::istringstream iss(line);
        std::string key, value;
        if (std::getline(iss, key, '=') && std::getline(iss, value)) {
            config_map_[key] = value;
        }
    }
    return true;
}

std::string config::get(const std::string &key, const std::string &default_val) const {
    auto it = config_map_.find(key);
    return it != config_map_.end() ? it->second : default_val;
}

int config::get_int(const std::string &key, int default_val) const {
    auto it = config_map_.find(key);
    if (it != config_map_.end()) {
        try {
            return std::stoi(it->second);
        } catch (...) {
            return default_val;
        }
    }
    return default_val;
}

} // namespace config
} // namespace hft
