// Copyright 2015 PKU-Cloud.
// Author : Chao Ma (mctt90@gmail.com)
//
#ifndef PARAMETER_ACCESSING_TABLE_H_
#define PARAMETER_ACCESSING_TABLE_H_

#include "src/util/bitmap.h"
#include "src/util/common.h"

#include <vector>

namespace brook {

//-------------------------------------------------------------
// AccessingTable is a list of bitmap to make a record that 
// which agent have accessed the parameters.
//-------------------------------------------------------------

class AccessingTable {

public:
    AccessingTable(uint32 bit_size, uint64 size) {
        CHECK_GT(bit_size, 0);
        CHECK_GT(size, 0);
        bit_size_ = bit_size;
        size_ = size;
        table_.resize(size_, Bitmap(bit_size_));
    }

    ~AccessingTable() {}

private:
    uint32 bit_size_;
    uint64 size_;
    std::vector<Bitmap> table_;
};

} // namespace

#endif // PARAMETER_ACCESSING_TABLE_H_
