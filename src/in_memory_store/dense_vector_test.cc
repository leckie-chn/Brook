// Copyright 2015 PKU-Cloud.
// Author: Chao Ma (mctt90@gmail.com)
//
#include <string>

#include "src/base/common.h"
#include "gtest/gtest.h"
#include "src/in_memory_store/dense_vector.h"

using brook::DenseVector;

typedef DenseVector<double> RealVector;

TEST(DenseVector, Scale) {
    RealVector v;
    v.push_back(2);
    v.push_back(4);
    Scale(&v, 0.5);
    EXPECT_EQ(v.size(), 2);
    EXPECT_EQ(v[0], 1);
    EXPECT_EQ(v[1], 2);
}

TEST(DenseVector, ScaleInto) {
    RealVector u, v;
    u.push_back(2);
    u.push_back(2);
    v.push_back(2);
    v.push_back(4);
    ScaleInto(&u, v, 0.5);
    EXPECT_EQ(u.size(), 2);
    EXPECT_EQ(u[0], 1);
    EXPECT_EQ(u[1], 2);
}

TEST(DenseVector, AddScaled) {
    RealVector u, v;
    u.push_back(2);
    u.push_back(0);
    u.push_back(0);
    v.push_back(0);
    v.push_back(2);
    v.push_back(4);
    AddScaled(&u, v, 0.5);
    EXPECT_EQ(u.size(), 3);
    EXPECT_EQ(u[0], 2);
    EXPECT_EQ(u[1], 1);
    EXPECT_EQ(u[2], 2);
}
