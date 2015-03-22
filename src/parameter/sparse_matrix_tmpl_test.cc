// Copyright 2015 PKU-Cloud
// Author : Chao Ma (mctt90@gmail.com)
//
#include "src/parameter/sparse_matrix_tmpl.h"
#include "src/parameter/sparse_vector_tmpl.h"

#include "gtest/gtest.h"

using brook::SparseVectorImpl;
using brook::SparseMatrixImpl;

typedef SparseVectorImpl<int32, double> RealMatrix;
typedef SparseMatrixImpl<int32, double> RealVector;

TEST(SparseMatrixImplTest, init) {

}
