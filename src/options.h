#include <memory>
#include "libs/cxxopts.hpp"

#pragma once

namespace options {
    void process_options(const cxxopts::ParseResult& parse_result, const cxxopts::Options& options);
    std::unique_ptr<cxxopts::Options> get_options();
}