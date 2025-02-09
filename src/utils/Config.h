// config.h
// author: mohammad bazrouk
// provides centralized configuration management to load and access system parameters.
#pragma once

#include <string>
#include <unordered_map>

namespace hft {
namespace config {

class config {
public:
    config();
    ~config();

    // load configuration from a file; returns true on success
    bool load(const std::string &filename);

    // get a configuration value as a string
    std::string get(const std::string &key, const std::string &default_val = "") const;

    // get a configuration value as an integer
    int get_int(const std::string &key, int default_val = 0) const;

private:
    std::unordered_map<std::string, std::string> config_map_;
};

} // namespace config
} // namespace hft
