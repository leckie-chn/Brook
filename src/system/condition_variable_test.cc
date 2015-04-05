// Copyright 2015 PKU-Cloud
// Author : Chao Ma (mctt90@gmail.com)
//
#include "gtest/gtest.h"
#include "src/system/condition_variable.h"

TEST(ConditionVariable, Init) {
    ConditionVariable cond;
}

TEST(ConditionVariable, Wait) {
    ConditionVariable event;
    event.Signal();
}

TEST(ConditionVariable, Release) {
}
