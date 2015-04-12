// Copyright 2015 PKU-Cloud.
// Author: Yan Ni(leckie.dove@gmail.com) &
//         Chao Ma (mctt90#gmail.com)
//
#ifndef UTIL_BITMAP_H_
#define UTIL_BITMAP_H_

#include "src/util/common.h"
#include "src/util/scoped_ptr.h"

#include <vector>
#include <cstring>

//-------------------------------------------------
// A naive implementation of Bitmap
//-------------------------------------------------
class Bitmap {
public:
    Bitmap(uint32 len, bool compress = false) {
        CHECK_GT(len, 0);
        bit_len_ = len;
        is_compressed_ = compress;
        bits_ = new char[bit_len_];
        memset(bits_, '\0', bit_len_);
    }

    ~Bitmap() {}

    void ElementList(std::vector<int>&);     // generate the element list.
    bool Test(int elem);                     // test the index of elem exists or not.
    void SetElement(int elem);               // set the index of numerber exists (1).
                                             // NOTE: index is based on zero.
    void UnsetElement(int elem);             // unset the index of number exists (0).
    void Clear();                            // set all bits zero.

private:
    uint32 bit_len_;              // the length of bitmap (int bytes).
    char* bits_;                  // bits are represent in char*
    bool is_compressed_;          // TODO: message compressing
};

#endif // UTIL_BITMAP_H_
