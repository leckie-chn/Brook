// Copyright 2015 PKU-Cloud.
// Author : Chao Ma (mctt90@gmail.com)
//
#include "src/consistency/fifo.h"

namespace brook {

const int MAXS = 20;

int Fifo::ReadNum() {
    int num = 0;
    file_ >> num;
    return num;
}

void Fifo::WriteNum(int num) {
    file_ << num;
} 

} // namespace brook;
