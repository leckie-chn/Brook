// Copyright 2015 PKU-Cloud
// Author : Chao Ma (mctt90@gmail.com)
//
#include "src/consistency/consistency.h"

namespace brook {

//-----------------------------------------------------------
// Implementation of Consistency
//-----------------------------------------------------------
void Consistency::Wait() {
   reader_count_ = FifoReadNum(reader_fp_);
}

void Consistency::Increase() {
    WriteNum(reader_count_+1, writer_fp_);
}

//-----------------------------------------------------------
// Implementation of BSP
//-----------------------------------------------------------
bool BSP::Judge() {
    return (reader_count_+1) == FifoReadNum(reader_fp_);
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
    return true;
}


} // namespace brook
