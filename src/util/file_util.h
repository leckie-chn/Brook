/*
This program is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 2 of the License, or (at
your option) any later version.

This program is distributed in the hope that it will be useful, but
WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA
02110-1301, USA.
*/
// Copyright 2015 PKU-Cloud.
// Author: Chao Ma (mctt90@gmail.com)

#ifndef UTIL_LITE_UTILS_H_
#define UTIL_LITE_UTILS_H_

#include <stdio.h>

#include "src/util/common.h"

inline FILE* OpenFileOrDie(const char* filename, const char* mode) {
  FILE* input_stream = fopen(filename, mode);
  if (input_stream == NULL) {
    LOG(FATAL) << "Cannot open file: " << filename << " with mode: " << mode;
  }
  return input_stream;
}

#endif  // UTIL_LITE_UTILS_H_
