// Copyright 2015 PKU-Cloud
// Author : Chao Ma (mctt90@gmail.com)
//
#include "src/consistency/consistency.h"

namespace brook {

//-----------------------------------------------------------
// Implementation of Consistency
//-----------------------------------------------------------
void Consistency::Wait() {
    cur_reader_count_ = OpenReadFifo(reader_fp_);
}

void Consistency::Increase() {
    cur_writer_count_++;
    WriteNum(cur_writer_count_, writer_fp_);
}

//-----------------------------------------------------------
// Implementation of BSP
//-----------------------------------------------------------
bool BSP::Judge() {
    if (last_reader_count_+1 == cur_reader_count_) {
        last_reader_count_ = cur_reader_count_;
        return true;
    }
    return false;
}

//-----------------------------------------------------------
// Implementation of Asychronous.
//-----------------------------------------------------------
bool Asychronous::Judge() {
    return true;
}

//-----------------------------------------------------------
// Implementation of SSP.
//-----------------------------------------------------------
bool SSP::Judge() {
    if (last_reader_count_)
}

} // namespace brook
