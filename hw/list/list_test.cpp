#include <gtest/gtest.h>
#include "list.h"

namespace {

TEST(ListTest, DefaultConstructor) {
    bmstu::list<int> list;
    EXPECT_EQ(list.size(), 0);
}

TEST(ListTest, InitializerListConstructor) {
    bmstu::list<int> list = {1, 2, 3, 4, 5};
    EXPECT_EQ(list.size(), 5);
    EXPECT_EQ(list[0], 1);
    EXPECT_EQ(list[1], 2);
    EXPECT_EQ(list[2], 3);
    EXPECT_EQ(list[3], 4);
    EXPECT_EQ(list[4], 5);
}

TEST(ListTest, PushFront) {
    bmstu::list<int> list;
    list.push_front(1);
    list.push_front(2);
    list.push_front(3);
    EXPECT_EQ(list.size(), 3);
    EXPECT_EQ(list[0], 3);
    EXPECT_EQ(list[1], 2);
    EXPECT_EQ(list[2], 1);
}

TEST(ListTest, PushBack) {
    bmstu::list<int> list;
    list.push_back(1);
    list.push_back(2);
    list.push_back(3);
    EXPECT_EQ(list.size(), 3);
    EXPECT_EQ(list[0], 1);
    EXPECT_EQ(list[1], 2);
    EXPECT_EQ(list[2], 3);
}

TEST(ListTest, Comparison) {
    bmstu::list<int> list1 = {1, 2, 3};
    bmstu::list<int> list2 = {1, 2, 3};
    bmstu::list<int> list3 = {1, 2, 4};

    EXPECT_TRUE(list1 == list2);
    EXPECT_FALSE(list1 == list3);
    EXPECT_TRUE(list1 != list3);
    EXPECT_TRUE(list1 < list3);
    EXPECT_TRUE(list1 <= list2);
    EXPECT_TRUE(list3 > list1);
    EXPECT_TRUE(list3 >= list1);
}

}  // namespace

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}