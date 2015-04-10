// Copyright 2015 PKU-Cloud
// Author : Chao Ma (mctt90@gmail.com)
//
#include "src/parameter/dense_vector_tmpl.h"

#include "gtest/gtest.h"

using brook::DenseVectorTmpl;

typedef DenseVectorTmpl<double> RealVector;

TEST(DenseVectorImplTest, Add) {
    RealVector u, v;
    u.push_back(1);
    u.push_back(2);
    v.push_back(1);
    v.push_back(2);
    u.Add(v);
    EXPECT_EQ(u.size(), 2);
    EXPECT_EQ(u[0], 2);
    EXPECT_EQ(u[1], 4);
}

TEST(DenseVectorImplTest, Minus) {
    RealVector u, v;
    u.push_back(2);
    u.push_back(3);
    v.push_back(1);
    v.push_back(2);
    u.Minus(v);
    EXPECT_EQ(u.size(), 2);
    EXPECT_EQ(u[0], 1);
    EXPECT_EQ(u[1], 1);
}

TEST(DenseVectorImplTest, Scale) {
    RealVector v;
    v.push_back(2);
    v.push_back(4);
    v.Scale(0.5);
    EXPECT_EQ(v.size(), 2);
    EXPECT_EQ(v[0], 1);
    EXPECT_EQ(v[1], 2);
}

TEST(DenseVectorImplTest, ScaleInto) {
    RealVector u, v;
    u.push_back(2);
    u.push_back(2);
    v.push_back(2);
    v.push_back(4);
    u.ScaleInto(v, 0.5);
    EXPECT_EQ(u.size(), 2);
    EXPECT_EQ(u[0], 1);
    EXPECT_EQ(u[1], 2);
}

TEST(DenseVectorImplTest, AddScaled) {
    RealVector u, v;
    u.push_back(2);
    u.push_back(0);
    u.push_back(0);
    v.push_back(0);
    v.push_back(2);
    v.push_back(4);
    u.AddScaled(v, 0.5);
    EXPECT_EQ(u.size(), 3);
    EXPECT_EQ(u[0], 2);
    EXPECT_EQ(u[1], 1);
    EXPECT_EQ(u[2], 2);
}

TEST(DenseVectorImplTest, AddScaledInto) {
    RealVector w, u, v;
    w.resize(3, 1);
    u.push_back(2);
    u.push_back(4);
    u.push_back(6);
    v.push_back(2);
    v.push_back(4);
    v.push_back(0);
    w.AddScaledInto(u, v, 0.5);
    EXPECT_EQ(w.size(), 3);
    EXPECT_EQ(w[0], 3);
    EXPECT_EQ(w[1], 6);
    EXPECT_EQ(w[2], 6);
}

TEST(DenseVectorImplTest, DotProduct) {
    RealVector v, u, w;
    v.push_back(1);
    v.push_back(0);
    u.push_back(0);
    u.push_back(1);
    w.push_back(1);
    w.push_back(1);
    EXPECT_EQ(v.DotProduct(u), 0);
    EXPECT_EQ(u.DotProduct(v), 0);
    EXPECT_EQ(v.DotProduct(w), 1);
    EXPECT_EQ(u.DotProduct(w), 1);
}
