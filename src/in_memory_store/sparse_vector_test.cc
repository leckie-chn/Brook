// Copyright 2015 PKU-Cloud.
// Author: Chao Ma (mctt90@gmail.com)
//
#include <string>
#include "src/base/common.h"
#include "gtest/gtest.h"
#include "src/in_memory_store/sparse_vector.h"

using brook::SparseVector;

typedef SparseVector<uint32, double> RealVector;

TEST(SparseVectorTest, SquareBrackets) {
    RealVector v;
    v.set(101, 1);
    EXPECT_EQ(v[101], 1);
    EXPECT_EQ(v[102], 0);
    EXPECT_EQ(v.has(101), true);
    EXPECT_EQ(v.has(102), false);
}

TEST(SparseVectorTest, Set) {
    RealVector v;
    EXPECT_EQ(v.size(), 0);
    v.set(101, 0);
    EXPECT_EQ(v.size(), 0);
    EXPECT_EQ(v.has(101), false);
    v.set(101, 1);
    EXPECT_EQ(v.size(), 1);
    EXPECT_EQ(v.has(101), true);
    EXPECT_EQ(v[101], 1);
    v.set(101, 2);
    EXPECT_EQ(v.size(), 1);
    EXPECT_EQ(v[101], 2);
    v.set(101, 0);
    EXPECT_EQ(v.size(), 0);
    EXPECT_EQ(v.has(101), false);
}

TEST(SparseVectorTest, Scale) {
    RealVector v;
    v.set(101, 2);
    v.set(102, 4);
    Scale(&v, 0.5);
    EXPECT_EQ(v.size(), 2);
    EXPECT_EQ(v[101], 1);
    EXPECT_EQ(v[102], 2);
}
