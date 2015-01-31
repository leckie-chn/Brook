// Copyright 2015 PKU-Cloud.
// Author: Chao Ma (mctt90@gmail.com)
//
#include <string>
#include <vector>

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

TEST(DenseVector, Replace) {
    RealVector v;
    v.push_back(0);
    v.push_back(1);
    std::vector<double> vc;
    vc.push_back(1);
    vc.push_back(2);
    Replace(&v, vc);
    EXPECT_EQ(v.size(), 2);
    EXPECT_EQ(v[0], 1);
    EXPECT_EQ(v[1], 2);

}

TEST(DenseVector, Add) {
    RealVector v;
    v.push_back(1);
    v.push_back(1);
    RealVector u;
    u.push_back(2);
    u.push_back(2);
    Add(&v, u);
    EXPECT_EQ(v.size(), 2);
    EXPECT_EQ(v[0], 3);
    EXPECT_EQ(v[1], 3);
}

TEST(DenseVector, Minus) {
   RealVector v;
   v.push_back(1);
   v.push_back(1);
   RealVector u;
   u.push_back(1);
   u.push_back(1);
   Minus(&v,u);
   EXPECT_EQ(v.size(), 2);
   EXPECT_EQ(v[0], 0);
   EXPECT_EQ(v[1], 0);
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

TEST(DenseVector, AddScaledInto) {
    RealVector w, u, v;
    w.resize(3, 1);
    u.push_back(2);
    u.push_back(4);
    u.push_back(6);
    v.push_back(2);
    v.push_back(4);
    v.push_back(0);
    AddScaledInto(&w, u, v, 0.5);
    EXPECT_EQ(w.size(), 3);
    EXPECT_EQ(w[0], 3);
    EXPECT_EQ(w[1], 6);
    EXPECT_EQ(w[2], 6);
}

TEST(DenseVector, DotProduct) {
    RealVector v, u, w;
    v.push_back(1);
    v.push_back(0);
    u.push_back(0);
    u.push_back(1);
    w.push_back(1);
    w.push_back(1);
    EXPECT_EQ(DotProduct(v, u), 0);
    EXPECT_EQ(DotProduct(u, v), 0);
    EXPECT_EQ(DotProduct(v, w), 1);
    EXPECT_EQ(DotProduct(u, w), 1);
}
