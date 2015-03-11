// Copyright : 2015 PKU-Cloud
// Author: Chao Ma (mctt90@gmail.com)
//
#include <string>

#include "src/base/common.h"
#include "gtest/gtest.h"
#include "src/in_memory_store/sparse_table.h"
#include "src/in_memory_store/sparse_table.h"

using brook::SparseVectorTmpl;
using brook::SparseTableTmpl;

typedef SparseVectorTmpl<uint32, double> RealVector;
typedef SparseTableTmpl<uint32, double> RealTable;

TEST(SparseTableTmpl, SetAndAccess) {
    RealVector v1;
    RealVector v2;
    v1.set(101, 1);
    v1.set(102, 2);
    v2.set(101, 1);
    v2.set(102, 2);
    RealTable t;
    t.set(0, v1);
    t.set(1, v2);
    t.push_back(v1);
    EXPECT_EQ(t.size(), 3);
    EXPECT_EQ(t[0][101], 1);
}
