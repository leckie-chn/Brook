// Copyright : 2015 PKU-Cloud
// Author: Chao Ma (mctt90@gmail.com)
//
#include <iostream>
#include <string>

#include "src/base/common.h"
#include "gtest/gtest.h"
#include "src/in_memory_store/sparse_table.h"
#include "src/in_memory_store/sparse_table.h"

using namespace std;
using brook::SparseVectorTmpl;
using brook::SparseTableTmpl;

typedef SparseVectorTmpl<uint32, double> RealVector;
typedef SparseTableTmpl<uint32, double> RealTable;

TEST(SparseTableTmpl, push_back) {
    RealVector v1;
    RealVector v2;
    v1.set(101, 1);
    v1.set(102, 2);
    v2.set(101, 1);
    v2.set(102, 2);
    RealTable t;
    t.push_back(v1);
    t.push_back(v2);
    t.push_back(v1);
    EXPECT_EQ(t.size(), 3);
    EXPECT_EQ(t[0][101], 1);
}

TEST(SparseTableTmpl, set) {
    RealVector v1;
    RealVector v2;
    v1.set(101, 1);
    v1.set(102, 2);
    v2.set(101, 1);
    v2.set(102, 2);
    RealTable t(2);
    t.set(0, v1);
    t.set(1, v2);
    EXPECT_EQ(t.size(), 2);
    EXPECT_EQ(t[1][1], 0);
}

TEST(SparseTableTmpl, scale) {
    RealVector v1;
    RealVector v2;
    v1.set(101, 1);
    v1.set(102, 2);
    v2.set(101, 1);
    v2.set(102, 2);
    RealTable t;
    t.push_back(v1);
    t.push_back(v2);
    TableScale(t, 0.5);
    EXPECT_EQ(t.size(), 2);
    EXPECT_EQ(t[0][101], 0.5);
    EXPECT_EQ(t[0][102], 1);
}
