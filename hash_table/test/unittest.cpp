#include <cstring>
#include <experimental/optional>
#include <iostream>
#include <map>
#include <memory>

#include "gtest/gtest.h"
#include "hash_table.hpp"

using namespace hashtable;

namespace {

TEST(HashTableTest, Find) {
    HashTable<uint64_t, uint64_t> table;

    auto computeValue = [](uint64_t key) { return key * 3; };

    size_t size = 1000;
    for (uint64_t i = 1; i <= size ; ++i) {
        table.insert(i, computeValue(i));
    }

    for (uint64_t i = 1; i <= size; ++i)
        EXPECT_EQ(std::experimental::optional<uint64_t>{computeValue(i)}, table.find(i));
}
    
TEST(HashTableTest, Remove) {
    HashTable<uint64_t, uint64_t> table;

    auto computeValue = [](uint64_t key) { return key * 3; };

    size_t size = 100;
    for (uint64_t i = 1; i <= size ; ++i) {
        table.insert(i, computeValue(i));
    }

    for (uint64_t i = 1; i <= size ; ++i) {
        table.remove(i);
        for (uint64_t j = 1; j <= size ; ++j) {
            if (j <= i)
                EXPECT_EQ(std::experimental::optional<uint64_t>{}, table.find(j));
            else 
                EXPECT_EQ(std::experimental::optional<uint64_t>{computeValue(j)}, table.find(j));
        }
    }
}

}