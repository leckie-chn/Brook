// Copyright 2015 PKU-Cloud.
// Author : Chao Ma (mctt90@gmail.com)
//
#include "src/parameter/dense_matrix_tmpl.h"
#include "src/parameter/dense_vector_tmpl.h"

#include "gtest/gtest.h"

using brook::DenseMatrixImpl;
using brook::DenseVectorImpl;

typedef DenseMatrixImpl<double> RealMatrix;
typedef DenseVectorImpl<double> RealVector;


TEST(DenseMatrixImplTest, init) {
    RealMatrix u;
    RealMatrix v(2, 2, 1);
    EXPECT_EQ(v.RowSize(), 2);
    EXPECT_EQ(v[0].size(), 2);
    EXPECT_EQ(v[0][1], 1);
    EXPECT_EQ(u.RowSize(), 0);
}

TEST(DenseMatrixImplTest, SetAndPush_back) {
    RealMatrix u;
    EXPECT_EQ(u.RowSize() ,0);
    RealVector v(2, 2);
    u.Push_back(v);
    u.Push_back(v);
    EXPECT_EQ(u.RowSize(), 2);
    EXPECT_EQ(u[1][1], 2);
    RealVector v2(2, 1);
    u.Set(1, v2);
    EXPECT_EQ(u[1][1], 1);
}

TEST(DenseMatrixImplTest, Add) {
    RealMatrix u(2, 2, 1);
    RealMatrix v(2, 2, 2);
    u.Add(v);
    EXPECT_EQ(u.RowSize(), 2);
    EXPECT_EQ(u[0][0], 3);
    EXPECT_EQ(u[1][1], 3); 
}

TEST(DenseMatrixImplTest, Minus) {
    RealMatrix u(2, 2, 1);
    RealMatrix v(2, 2, 2);
    u.Minus(v);
    EXPECT_EQ(u.RowSize(), 2);
    EXPECT_EQ(u[0][0], -1);
    EXPECT_EQ(u[1][1], -1);
}

TEST(DenseMatrixImplTest, Scale) {
    RealMatrix u(2, 2, 1);
    u.Scale(0.5);
    EXPECT_EQ(u.RowSize(), 2);
    EXPECT_EQ(u[0][0], 0.5);
    EXPECT_EQ(u[1][1], 0.5);
}

TEST(DenseMatrixImplTest, ScaleInto) {
    RealMatrix u(2, 2, 1);
    RealMatrix v(2, 2, 2);
    u.ScaleInto(v, 2);
    EXPECT_EQ(u.RowSize(), 2);
    EXPECT_EQ(u[0][0], 4);
    EXPECT_EQ(u[1][1], 4);
}

TEST(DenseMatrixImplTest, AddScaled) {
    RealMatrix u(2, 2, 1);
    RealMatrix v(2, 2, 2);
    u.AddScaled(v, 2);
    EXPECT_EQ(u.RowSize(), 2);
    EXPECT_EQ(u[0][0], 5);
    EXPECT_EQ(u[1][1], 5);
}

TEST(DenseMatrixImplTest, AddScaledInto) {
    RealMatrix u(2, 2, 1);
    RealMatrix v(2, 2, 2);
    RealMatrix w(2, 2, 2);
    u.AddScaledInto(v, w, 1);
    EXPECT_EQ(u.RowSize(), 2);
    EXPECT_EQ(u[0][0], 4);
    EXPECT_EQ(u[1][1], 4);
}
