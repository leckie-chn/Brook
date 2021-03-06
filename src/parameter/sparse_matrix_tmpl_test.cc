// Copyright 2015 PKU-Cloud
// Author : Chao Ma (mctt90@gmail.com)
//
#include "src/parameter/sparse_matrix_tmpl.h"
#include "src/parameter/sparse_vector_tmpl.h"

#include "gtest/gtest.h"

using brook::SparseVectorTmpl;
using brook::SparseMatrixTmpl;

typedef SparseVectorTmpl<int32, double> RealVector;
typedef SparseMatrixTmpl<int32, double> RealMatrix;

TEST(SparseMatrixTmplTest, init) {
    RealMatrix u;
    RealMatrix v(2);
    EXPECT_EQ(u.RowSize(), 0);
    EXPECT_EQ(v.RowSize(), 2);
}

TEST(SparseMatrixTmplTest, SetAndPush_back) {
    RealMatrix u;
    EXPECT_EQ(u.RowSize(), 0);
    RealVector v;
    v.set(101, 1);
    v.set(102, 2);
    u.Push_back(v);
    u.Push_back(v);
    EXPECT_EQ(u.RowSize(), 2);
    EXPECT_EQ(u[0][101], 1);
    EXPECT_EQ(u[1][102], 2);
    v.set(101, 2);
    u.Set(0, v);
    EXPECT_EQ(u[0][101], 2);
}

TEST(SparseMatrixTmplTest, Add) {
    RealMatrix u, v;
    RealVector w;
    w.set(101, 1);
    w.set(102, 2);
    u.Push_back(w);
    v.Push_back(w);
    u.Add(v);
    EXPECT_EQ(u.RowSize(), 1);
    EXPECT_EQ(u[0][101], 2);
    EXPECT_EQ(u[0][102], 4);
}

TEST(SparseMatrixTmplTest, Minus) {
    RealMatrix u, v;
    RealVector w, y;
    w.set(101, 2);
    w.set(102, 4);
    y.set(101, 1);
    y.set(102, 2);
    u.Push_back(w);
    v.Push_back(y);
    u.Minus(v);
    EXPECT_EQ(u.RowSize(), 1);
    EXPECT_EQ(u[0][101], 1);
    EXPECT_EQ(u[0][102], 2);
}

TEST(SparseMatrixTmplTest, Scale) {
    RealMatrix v;
    RealVector u;
    u.set(101, 1);
    u.set(102, 2);
    v.Push_back(u);
    v.Scale(0.5);
    EXPECT_EQ(v.RowSize(), 1);
    EXPECT_EQ(v[0][101], 0.5);
    EXPECT_EQ(v[0][102], 1);
}

TEST(SparseMatrixTmplTest, ScaleInto) {
    RealMatrix u, v;
    RealVector w;
    w.set(101, 1);
    w.set(102, 2);
    v.Push_back(w);
    u.Push_back(w);
    u.ScaleInto(v, 2);
    EXPECT_EQ(u.RowSize(), 1);
    EXPECT_EQ(u[0][101], 2);
    EXPECT_EQ(u[0][102], 4);
}

TEST(SparseMatrixTmplTest, AddScaled) {
    RealMatrix u, v;
    RealVector w;
    w.set(101, 1);
    w.set(102, 2);
    v.Push_back(w);
    u.Push_back(w);
    u.AddScaled(v, 2);
    EXPECT_EQ(u.RowSize(), 1);
    EXPECT_EQ(u[0][101], 3);
    EXPECT_EQ(u[0][102], 6);
}

TEST(SparseMatrixTmplTest, AddScaledInto) {
    RealMatrix u,v,w;
    RealVector y;
    y.set(101, 1);
    y.set(102, 2);
    u.Push_back(y);
    v.Push_back(y);
    w.Push_back(y);
    u.AddScaledInto(v, w, 2);
    EXPECT_EQ(u.RowSize(), 1);
    EXPECT_EQ(u[0][101], 3);
    EXPECT_EQ(u[0][102], 6);
}
