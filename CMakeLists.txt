# CMakeLists.txt
# author: mohammad bazrouk
# cmake configuration for the hft trading system

cmake_minimum_required(VERSION 3.10)
project(hft_trading_system)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3 -march=native -pthread")

# include directories
include_directories(${PROJECT_SOURCE_DIR}/src)
include_directories(${PROJECT_SOURCE_DIR}/utils)
include_directories(${PROJECT_SOURCE_DIR}/include)

# gather source files
file(GLOB_RECURSE SRC_CORE "src/core/*.cpp")
file(GLOB_RECURSE SRC_INFRA "src/infrastructure/*.cpp")
file(GLOB_RECURSE SRC_STRAT "src/strategies/*.cpp")
file(GLOB_RECURSE UTILS "utils/*.cpp")

# main executable
add_executable(hft_trading_system_executable
    src/main.cpp
    ${SRC_CORE}
    ${SRC_INFRA}
    ${SRC_STRAT}
    ${UTILS}
)

# add tests (optional)
enable_testing()
add_subdirectory(tests)
