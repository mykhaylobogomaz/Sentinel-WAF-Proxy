cmake_minimum_required(VERSION 3.15)
project(SentinelWAFProxy)

set(CMAKE_CXX_STANDARD 20)

include(FetchContent)

FetchContent_Declare(asio URL https://github.com/chriskohlhoff/asio/archive/refs/tags/asio-1-30-2.tar.gz)
FetchContent_MakeAvailable(asio)

FetchContent_Declare(nlohmann_json URL https://github.com/nlohmann/json/archive/refs/tags/v3.11.3.tar.gz)
FetchContent_MakeAvailable(nlohmann_json)

FetchContent_Declare(googletest URL https://github.com/google/googletest/archive/refs/tags/v1.14.0.tar.gz)
FetchContent_MakeAvailable(googletest)

add_library(asio_interface INTERFACE)
target_include_directories(asio_interface INTERFACE ${asio_SOURCE_DIR}/asio/include)
target_compile_definitions(asio_interface INTERFACE ASIO_STANDALONE)

add_library(json_interface INTERFACE)
target_include_directories(json_interface INTERFACE ${nlohmann_json_SOURCE_DIR}/include)

add_executable(waf_proxy src/proxy/proxy.cpp)
target_link_libraries(waf_proxy PRIVATE asio_interface json_interface)
target_compile_definitions(waf_proxy PRIVATE _WIN32_WINNT=0x0601)

enable_testing()
add_executable(waf_tests tests/test_runner.cpp)
target_link_libraries(waf_tests PRIVATE GTest::gtest asio_interface json_interface)
target_compile_definitions(waf_tests PRIVATE _WIN32_WINNT=0x0601)
add_test(NAME WAFTests COMMAND waf_tests)
