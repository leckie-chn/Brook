// Copyright 2015 PKU-Cloud.
// Author : Chao Ma (mctt90@gmail.com)
//

#include "src/parameter/update_tmpl.h"
#include "src/parameter/dense_vector_tmpl.h"

#include "gtest/gtest.h"

using namespace brook;

typedef GDUpdaterTmpl<double> GDUpdater;
typedef GAUpdaterTmpl<double> GAUpdater;
typedef DenseVectorTmpl<double> DenseVector;


TEST(GDUpdater, TEST) {
    GDUpdater gdu;
    DenseVector para(2, 0.0);
    DenseVector gradients(2, 1.0);
    gdu.Update(para, gradients);
    EXPECT_EQ(para.size(), 2);
    EXPECT_EQ(para[0], 1.0);
    EXPECT_EQ(para[1], 1.0);
}

TEST(GAUpdater, TEST) {
    GAUpdater gau;
    DenseVector para(2, 2.0);
    DenseVector gradients(2, 1.0);
    gau.Update(para, gradients);
    EXPECT_EQ(para.size(), 2);
    EXPECT_EQ(para[0], 1.0);
    EXPECT_EQ(para[1], 1.0);
}
