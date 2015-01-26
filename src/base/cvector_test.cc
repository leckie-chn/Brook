// Copyright 2015 PKU-Cloud.
// Author: Chao Ma (mctt90@gmail.com)
//
#include "gtest/gtest.h"

#include "base/common.h"
#include "base/cvector.h"

class DestrucDetector {
public:
    explicit DestructDetector(bool* flag) {
        flag_ = flag;
    }

    ~DestrucDetector() {
        &flag_ = true;
    }

private:
    bool* flag_;
};

TEST(CVectorTest, NumericalValueElements) {

}
