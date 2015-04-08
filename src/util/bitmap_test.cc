// Copyright 2015 PKU-Cloud.
// Author: Yan Ni(leckie.dove@gmail.com) &
//         Chao Ma (mctt90@gmail.com)
//
#include "src/util/bitmap.h"

#include "gtest/gtest.h"

using namespace std;

TEST(BitmapTest, Init) {
    Bitmap bp(100);
}

TEST(BitmapTest, SetElement) {
    Bitmap bp(100);
    bp.SetElement(52);
    EXPECT_EQ(bp.Test(52), true);
    EXPECT_EQ(bp.Test(32), false);
}

TEST(BitmapTest, Unset) {
    Bitmap bp(100);
    bp.SetElement(52);
    EXPECT_EQ(bp.Test(52), true);
    bp.UnsetElement(52);
    EXPECT_EQ(bp.Test(52), false);
}

TEST(BitmapTest, EmmentList) {
    Bitmap bp(100);
    bp.SetElement(2);
    bp.SetElement(10);
    bp.SetElement(88);
    vector<int> vec;
    bp.ElementList(vec);
    EXPECT_EQ(vec.size(), 3);
    EXPECT_EQ(vec[0], 2);
    EXPECT_EQ(vec[1], 10);
    EXPECT_EQ(vec[2], 88);
}
