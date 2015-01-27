// Copyright 2014 PKU-Cloud
// Author: Chao Ma (mctt90@gmail.com)
//
#include "src/mrml/utils.h"

#include "gtest/gtest.h"

TEST(MapReduceUtils, CreateNonExistingFile) {
    EXPECT_TRUE(OpenFileOrDie("/tmp/a-non-existing-file", "w") != NULL);
}
