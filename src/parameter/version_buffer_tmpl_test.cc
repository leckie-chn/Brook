// Copyright 2015 PKU-Cloud.
// Author : Chao Ma (mctt90@gmail.com)
//

#include "src/parameter/version_buffer_tmpl.h"

#include <iostream>

#include "gtest/gtest.h"

using namespace std;
using namespace brook;

typedef VersionBufferTmpl<float> VersionBuffer;

TEST(VersionBufferTest, SetAndGet) {
    // feature_num = 3, bit_size = 3, num_agent = 3;
    VersionBuffer buffer(3, 3, 3);   
    buffer.Set(0, 0, (float)0.1);
    buffer.Set(1, 0, (float)0.2);
    buffer.Set(2, 0, (float)0.3);
}
