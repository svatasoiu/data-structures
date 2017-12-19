#include <cstring>
#include <memory>

#include "gtest/gtest.h"
#include "skip_list.hpp"

using namespace skiplist;

namespace {

TEST(SkipListTest, Find) {
    SkipList<int, int> skiplist;
    skiplist.insert(3, 6);
    EXPECT_EQ(6, skiplist.find(3));
}

}