// Copyright 2015 PKU-Cloud.
// Author: Chao Ma (mctt90@gmail.com)
//
#include <string>
#include <iostream>
#include <map>
#include "src/base/common.h"
#include "gtest/gtest.h"
#include "src/in_memory_store/sparse_vector.h"

using brook::SparseVector;
using std::pair;

typedef SparseVector<uint32, double> RealVector;

TEST(SparseVectorTest, SquareBrackets) {
    RealVector v;
    v.set(101, 1);
    EXPECT_EQ(v[101], 1);
    EXPECT_EQ(v[102], 0);
    EXPECT_EQ(v.has(101), true);
    EXPECT_EQ(v.has(102), false);
}

TEST(SparseVectorTest, Add) {
    RealVector v;
    v.set(0, 1);
    v.set(1, 1);
    v.set(3, 1);
    RealVector u;
    u.set(2, 1);
    u.set(3, 2);
    u.set(4, 1);
    Add(&v, u);
    EXPECT_EQ(v.size(), 5);
    EXPECT_EQ(v[0], 1);
    EXPECT_EQ(v[1], 1);
    EXPECT_EQ(v[2], 1);
    EXPECT_EQ(v[3], 3);
    EXPECT_EQ(v[4], 1);
}

TEST(SparseVectorTest, AddMap) {
    RealVector v;
    v.set(0, 1);
    v.set(1, 1);
    v.set(2, 1);
    std::map<uint32, double> mp;
    mp.insert(pair<uint32, double>(0, 1));
    mp.insert(pair<uint32, double>(1, 1));
    mp.insert(pair<uint32, double>(2, 1));
    Add(&v, mp);
    EXPECT_EQ(v.size(), 3);
    EXPECT_EQ(v[0], 2);
    EXPECT_EQ(v[1], 2);
    EXPECT_EQ(v[2], 2);
}

TEST(SparseVectorTest, Minus) {
    RealVector v;
    v.set(0, 1);
    v.set(1, 2);
    v.set(2, 3);
    RealVector u;
    u.set(0, 1);
    u.set(1, 1);
    u.set(3, 1);
    Minus(&v, u);
    EXPECT_EQ(v.size(), 3);
    EXPECT_EQ(v[1], 1);
    EXPECT_EQ(v[2], 3);
    EXPECT_EQ(v[3], -1);
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

TEST(SparseVectorTest, ScaleInto) {
    RealVector u, v;
    u.set(200, 2);
    v.set(101, 2);
    v.set(102, 4);
    ScaleInto(&u, v, 0.5);
    EXPECT_EQ(u.size(), 2);
    EXPECT_EQ(u[101], 1);
    EXPECT_EQ(u[102], 2);
}

TEST(SparseVectorTest, AddScaled) {
    RealVector u, v;
    u.set(200, 2);
    v.set(101, 2);
    v.set(102, 4);
    AddScaled(&u, v, 0.5);
    EXPECT_EQ(u.size(), 3);
    EXPECT_EQ(u[200], 2);
    EXPECT_EQ(u[101], 1);
    EXPECT_EQ(u[102], 2);
}

TEST(SparseVectorTest, AddScaledInto) {
    RealVector w, u, v;
    w.set(200, 100);
    u.set(101, 2);
    u.set(102, 4);
    u.set(301, 8);
    u.set(302, 100);
    v.set(101, 2);
    v.set(103, 6);
    v.set(301, 8);
    AddScaledInto(&w, u, v, 0.5);
    EXPECT_EQ(w.size(), 5);
    EXPECT_EQ(w[101], 3);
    EXPECT_EQ(w[102], 4);
    EXPECT_EQ(w[103], 3);
    EXPECT_EQ(w[301], 12);
    EXPECT_EQ(w[302], 100);
}

TEST(SparseVectorTest, DotProduct) {
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

TEST(SparseVectorTest, Output) {
    RealVector v;
    v.set(0, 1);
    v.set(1, 2);
    v.set(2, 3);
    std::cout << v << std::endl;
    std::ofstream fout("/tmp/test_output");
    fout << v << std::endl;
}
