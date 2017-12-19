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

    size_t size = 50;
    for (uint64_t i = 1; i <= size ; ++i) {
        // std::cout << i << std::endl;
        skiplist.insert(i, i * 3);
    }

    skiplist.print(std::cout);
    skiplist.insert(size + 1, 3 * (size + 1));
    skiplist.print(std::cout);

    for (uint64_t i = 1; i <= size+1; ++i)
        EXPECT_EQ(std::experimental::optional<uint64_t>{i * 3}, skiplist.find(i));
}

}