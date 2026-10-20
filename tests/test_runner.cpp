#include "../src/proxy/proxy.hpp"
#include <cassert>
#include <iostream>

int main() {
    // Test 1: Buffer
    std::string err;
    std::string large_body(MAX_BODY_SIZE + 1, 'a');
    assert(!is_valid_json(large_body, err));
    assert(err == "Size limit");

    // Test 2: JSON
    std::string bad_json = "{\"key\": \"val\"}\x01";
    assert(!is_valid_json(bad_json, err));
    assert(err == "Control chars");

    // Test 3: CB
    cb.record_failure();
    cb.record_failure();
    cb.record_failure();
    assert(cb.is_open);

    std::cout << "All tests passed." << std::endl;
    return 0;
}
