// Copyright 2014 PKU-Cloud.
// Author: Choa Ma (mctt90@gmail.com)
//
#include "src/base/file_util.h"

#include "gtest/gtest.h"

TEST(FILE_UTIL_TEST, CreateNonExistingFile) {
    EXPECT_TRUE(OpenFileOrDie("/tmp/a-non-existing-file", "w") != NULL);
}
