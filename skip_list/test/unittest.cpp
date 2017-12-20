#include <cstring>
#include <experimental/optional>
#include <iostream>
#include <map>
#include <memory>

#include "gtest/gtest.h"
#include "skip_list.hpp"

namespace {

TEST(SkipListTest, Find) {
    skiplist::SkipList<uint64_t, uint64_t> skiplist;

    auto computeValue = [](uint64_t key) { return key * 3; };

    size_t size = 10000;
    for (uint64_t i = 1; i <= size ; ++i) {
        skiplist.insert(i, computeValue(i));
    }

    for (uint64_t i = 1; i <= size; ++i)
        EXPECT_EQ(std::experimental::optional<uint64_t>{computeValue(i)}, skiplist.find(i));
}
    
TEST(SkipListTest, Remove) {
    skiplist::SkipList<uint64_t, uint64_t> skiplist;

    auto computeValue = [](uint64_t key) { return key * 3; };

    size_t size = 1000;
    for (uint64_t i = 1; i <= size ; ++i) {
        skiplist.insert(i, computeValue(i));
    }

    for (uint64_t i = 1; i <= size ; ++i) {
        skiplist.remove(i);
        for (uint64_t j = 1; j <= size ; ++j) {
            if (j <= i)
                EXPECT_EQ(std::experimental::optional<uint64_t>{}, skiplist.find(j));
            else 
                EXPECT_EQ(std::experimental::optional<uint64_t>{computeValue(j)}, skiplist.find(j));
        }
    }
}

}