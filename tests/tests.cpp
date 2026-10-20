#include <gtest/gtest.h>
#include "../src/proxy/proxy.cpp" // Для простоты тестов

TEST(WAFTest, BufferLimit) {
    std::string err;
    std::string large_body(MAX_BODY_SIZE + 1, 'a');
    EXPECT_FALSE(is_valid_json(large_body, err));
    EXPECT_EQ(err, "Size limit");
}

TEST(WAFTest, JSONSmuggling) {
    std::string err;
    std::string bad_json = "{\"key\": \"val\"}\x01"; // Control char
    EXPECT_FALSE(is_valid_json(bad_json, err));
    EXPECT_EQ(err, "Control chars");
}

TEST(CBTest, StateChange) {
    cb.record_failure();
    cb.record_failure();
    cb.record_failure();
    EXPECT_TRUE(cb.is_open);
}
