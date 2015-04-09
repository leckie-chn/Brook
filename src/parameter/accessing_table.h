// Copyright 2015 PKU-Cloud.
// Author : Chao Ma (mctt90@gmail.com)
//
#ifndef PARAMETER_ACCESSING_TABLE_H_
#define PARAMETER_ACCESSING_TABLE_H_

#include "src/util/bitmap.h"

#include <vector>

namespace brook {

class AccessingTable {

public:

private:

    std::vector<Bitmap> table_;
};

} // namespace

#endif // PARAMETER_ACCESSING_TABLE_H_
