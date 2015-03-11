// Copyright : 2015 PKU-Cloud
// Author: Chao Ma (mctt90@gmail.com)
//
#include <iostream>
#include <string>

#include "src/base/common.h"
#include "gtest/gtest.h"
#include "src/in_memory_store/dense_table.h"

using namespace std;
using brook::DenseVectorTmpl;
using brook::DenseTableTmpl;

typedef DenseVectorTmpl<double> RealVector;
typedef DenseTableTmpl<double> RealTable;

TEST(DenseTableTmpl, push_back) {
    RealVector v1, v2;
    v1.push_back(1);
    v1.push_back(2);
    v2.push_back(2);
    v2.push_back(3);
    RealTable t;
    t.push_back(v1);
    t.push_back(v2);
    EXPECT_EQ(t.size(), 2);
    EXPECT_EQ(t[0][0], 1);
}

TEST(DenseTableTmpl, set) {
    RealVector v1, v2;
    v1.push_back(0);
    v1.push_back(1);
    v2.push_back(0);
    v2.push_back(2);
    RealTable t(2);
    t.set(0, v1);
    t.set(1, v2);
    EXPECT_EQ(t.size(), 2);
    EXPECT_EQ(t[1][1], 2);
}

TEST(DenseTableTmpl, scale) {
    RealVector v1, v2;
    v1.push_back(101);
    v1.push_back(102);
    v2.push_back(101);
    v2.push_back(102);
    RealTable t;
    t.push_back(v1);
    t.push_back(v2);
    TableScale(t, 0);
    EXPECT_EQ(t.size(), 2);
    EXPECT_EQ(t[0][0], 0);
}

TEST(DenseTableTmpl, scaleinto) {
    RealVector v1, v2;
    v1.push_back(101);
    v1.push_back(102);
    v2.push_back(101);
    v2.push_back(102);
    RealTable t1, t2;
    t1.push_back(v1);
    t2.push_back(v2);
    TableScaleInto(t1, t2, 0);
    EXPECT_EQ(t1.size(), 1);
    EXPECT_EQ(t1[0][0], 0);
}
