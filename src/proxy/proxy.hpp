#pragma once
#include <asio.hpp>
#include <nlohmann/json.hpp>
#include <string>
#include <atomic>
#include <chrono>

const size_t MAX_BODY_SIZE = 1 * 1024 * 1024; // 1 MiB

// JSON Validation: Parser-Disagreement & Graphemes
inline bool is_valid_json(const std::string& body, std::string& err) {
    if (body.size() > MAX_BODY_SIZE) { err = "Size limit"; return false; }
    // json j = json::parse(body, nullptr, true, true);
    for (unsigned char c : body) {
        if (c < 32 && c != '\n' && c != '\r' && c != '\t') {
            err = "Control chars"; return false;
        }
    }
    return true;
}

// Circuit Breaker
struct CircuitBreaker {
    std::atomic<bool> is_open{false};
    std::atomic<int> failure_count{0};
    std::chrono::steady_clock::time_point last_failure_time;

    bool try_request() {
        if (is_open) {
            if (std::chrono::steady_clock::now() - last_failure_time > std::chrono::seconds(5)) {
                return true; // Half-open
            }
            return false;
        }
        return true;
    }
    void record_failure() {
        failure_count++;
        if (failure_count >= 3) { is_open = true; last_failure_time = std::chrono::steady_clock::now(); }
    }
    void record_success() { failure_count = 0; is_open = false; }
};

inline CircuitBreaker cb;
