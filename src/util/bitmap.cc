// Copyright 2015 PKU-Cloud.
// Author: Yan Ni(leckie.dove@gmail.com)
//         Chao Ma (mctt90@gmail.com)

#include "src/util/bitmap.h"
#include "snappy.h"

#define CHAR_SIZE 8  // NOTE: do not use sizeof(char), because 
                     // this may bring much more overhead when 
                     // we invoke these functions (as follows) 
                     // very frequently.

#define BIT_TO_BYTE(X) ((X) / CHAR_SIZE)
#define OFFSET(X) ((X) % CHAR_SIZE)

void Bitmap::ElementList(std::vector<int>& vec) {
    for (int i = 0 ; i < bit_len_ ; i++) {
        for (int j = 0 ; j < CHAR_SIZE ; j++) {
            if (((unsigned char)(bits_[i]) & (1 << j)) > 0) {
                vec.push_back(i * CHAR_SIZE + j);
            }
        }
    }
}

bool Bitmap::Test(int elem) {
    CHECK_GE(elem, 0);
    CHECK_LT(elem, bit_len_);
    return ((bits_[BIT_TO_BYTE(elem)] & (1 << OFFSET(elem))) > 0);
}

void Bitmap::SetElement(int elem) {
    CHECK_GE(elem, 0);
    CHECK_LT(elem, bit_len_);
    (bits_[BIT_TO_BYTE(elem)] |= 1 << OFFSET(elem));
}

void Bitmap::UnsetElement(int elem) {
    CHECK_GE(elem, 0);
    CHECK_LT(elem, bit_len_);
    (bits_[BIT_TO_BYTE(elem)] &= ~(1 << OFFSET(elem)));
}

void Bitmap::Clear() {
    memset(bits_, '\0', bit_len_);
}
