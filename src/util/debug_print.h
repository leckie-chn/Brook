// Copyright 2015 PKU-Cloud.
// Author : Chao Ma (mctt90@gmail.com)
//
// debug_print is a tool for debuging.
//
#ifndef UTIL_DEBUG_PRINT_H_
#define UTIL_DEBUG_PRINT_H_

#include <iostream>

#define DEBUG_PRINT(a) {               \
    std::cout << a;                    \
}

#define DEBUG_PRINT_LINE(a) {          \
    std::cout << a << std::endl;       \
}

#endif // UTIL_DEBUG_PRINT_H_
