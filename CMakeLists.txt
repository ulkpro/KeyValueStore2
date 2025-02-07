cmake_minimum_required(VERSION 3.16)
project(KeyValueStore2)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(${PROJECT_SOURCE_DIR}/include)

find_package(nlohmann_json CONFIG REQUIRED)

add_executable(KeyValueStore2 src/main.cpp src/KeyValueStore.cpp "src/Cache.cpp" "include/Cache.h")

target_link_libraries(KeyValueStore2 PRIVATE nlohmann_json::nlohmann_json)
