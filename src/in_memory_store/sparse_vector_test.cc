// Copyright: 2015 PKU-Cloud.
// Author: Chao Ma (mctt90@gmail.com)
//
#include <string>

#include "src/base/common.h"
#include "gtest/gtest.h"
#include "src/in_memory_store/sparse_vector.h"

using brook::SparseVectorTmpl;

typedef SparseVectorTmpl<uint32, double> RealVector;

TEST(SparseVectorTmpl, SquareBrackets) {
    RealVector v;
    v.set(101, 1);
    EXPECT_EQ(v[101], 1);
    EXPECT_EQ(v[102], 0);
    EXPECT_EQ(v.has(101), true);
    EXPECT_EQ(v.has(102), false);
}

TEST(SparseVectorTmpl, Set) {
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
    EXPECT_EQ(v.has(101), true);
    EXPECT_EQ(v[101], 2);
    v.set(101, 0);
    EXPECT_EQ(v.size(), 0);
    EXPECT_EQ(v.has(101), false);
}

TEST(SparseVectorTmpl, Scale) {
    RealVector v;
    v.set(101, 2);
    v.set(102, 4);
    Scale(v, 0.5);
    EXPECT_EQ(v.size(), 2);
    EXPECT_EQ(v[101], 1);
    EXPECT_EQ(v[102], 2);
}

TEST(SparseVectorTmpl, ScaleInto) {
    RealVector u, v;
    u.set(200, 2);
    v.set(101, 2);
    v.set(102, 4);
    ScaleInto(u, v, 0.5);
    EXPECT_EQ(u.size(), 2);
    EXPECT_EQ(u[101], 1);
    EXPECT_EQ(u[102], 2);
}

TEST(SparseVectorTmpl, AddScaled) {
    RealVector u, v;
    u.set(200, 2);
    v.set(101, 2);
    v.set(102, 4);
    AddScaled(u, v, 0.5);
    EXPECT_EQ(u[200], 2);
    EXPECT_EQ(u[101], 1);
    EXPECT_EQ(u[102], 2);
}

TEST(SparseVectorTmpl, AddScaledInto) {
    RealVector w, u, v;
    w.set(200 ,100);
    u.set(101, 2);
    u.set(102, 4);
    u.set(301, 8);
    u.set(302, 100);
    v.set(101, 2);
    v.set(103, 6);
    v.set(301, 8);
    AddScaleInto(w, u, v, 0.5);
    EXPECT_EQ(w.size(), 5);
    EXPECT_EQ(w[101], 3);
    EXPECT_EQ(w[102], 4);
    EXPECT_EQ(w[103], 3);
    EXPECT_EQ(w[301], 12);
    EXPECT_EQ(w[302], 100);
}

TEST(SparseVectorTmpl, DotProduct) {
    RealVector v, u, w;
    v.set(101, 2);
    v.set(102, 4);
    v.set(301, 9);
    v.set(302, 100);
    u.set(101, 2);
    u.set(103, 6);
    u.set(301, 9);
    w.set(200, 10);
    EXPECT_EQ(DotProduct(v, u), 85);
    EXPECT_EQ(DotProduct(u, v), 85);
    EXPECT_EQ(DotProduct(v, w), 0);
    EXPECT_EQ(DotProduct(u, w), 0);
}
