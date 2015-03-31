// Copyright 2015 PKU-Cloud.
// Auhtor : Chao Ma (mctt90@gmail.com)
//
#include "gtest/gtest.h"

#include "src/util/common.h"
#include "src/util/carray_vector_tmpl.h"

class DestructDetector {
public:
    explicit DestructDetector(bool* flag) {
        flag_ = flag;
    }
    ~DestructDetector() {
        *flag_ = true;
    }
private:
    bool* flag_;
};
