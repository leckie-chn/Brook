// Copyright 2014 PKU-Cloud.
// Author: Chao Ma (mctt90@gmail.com)
//
#ifndef BASE_FILE_UTIL_H_
#define BASE_FILE_UTIL_H_

#include <stdio.h>

#include "src/base/common.h"

inline FILE* OpenFileOrDie(const char* filename, const char* mode) {
    FILE* input_stream = fopen(filename, mode);
    if (input_stream == NULL) {
        LOG(FATAL) << "Cannot open file: " << filename << " with mode: " << mode;
    }
    return input_stream;
}

#endif // BASE_FILE_UTIL_H_
