// Copyright 2015 PKU-Cloud
// Author : Chao Ma (mctt90@gmail.com)
//
#include "src/consistency/consistency.h"

namespace brook {

//-----------------------------------------------------------
// Implementation of Consistency.
//-----------------------------------------------------------
void Consistency::IncreaseSignal() {
    // Either agent or user process increases the timestamp,
    // and write it to fifo file after completing their work.
    WriteNum(++timestamp_, writer_fp_);
}

//-----------------------------------------------------------
// Implementation of AgentConsistency.
//-----------------------------------------------------------
void AgentConsistency::WaitSignal() {
    // For a agent process, agent read the update when the 
    // signal is comming. Agent don't care about the num of
    // this signal. Just send them to server.
    FifoReadNum(reader_fp_);
}

//-----------------------------------------------------------
// Implementation of UserConsistency.
//-----------------------------------------------------------
void UserConsistency::WaitSignal() {
    while (true) {
        if (Judge()) break;
        last_timestamp_ = FifoReadNum(reader_fp_);
    }
}

//-----------------------------------------------------------
// Implementation of BSP.
//-----------------------------------------------------------
bool BSP::Judge() {
    return timestamp_ == last_timestamp_;
}

//-----------------------------------------------------------
// Implementation of Asynchronism.
//-----------------------------------------------------------
bool Asy::Judge() {
    return true;
}

//-----------------------------------------------------------
// Implementation of SSP.
//-----------------------------------------------------------
bool SSP::Judge() {
    return timestamp_ <= last_timestamp_ + bounded_staleness_;
}

} // namespace brook
