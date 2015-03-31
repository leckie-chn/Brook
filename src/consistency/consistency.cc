// Copyright 2015 PKU-Cloud
// Author : Chao Ma (mctt90@gmail.com)
//
#include "src/consistency/consistency.h"

namespace brook {

//-----------------------------------------------------------
// Implementation of AgentConsistency.
//-----------------------------------------------------------
void AgentConsistency::WaitSignal() {
    // For a agent process, agent read the update when the 
    // signal is comming. Agent don't care about the num of
    // this signal. Just send them to server.
    FifoReadNum(reader_fp_);
}

void AgentConsistency::IncreaseSignal() {
    // For a agent process, agent recv the parameter from server,
    // and then write them to in-memory file. Finally, increase the 
    // timestamp of current fifo file.
    WriteNum(++timestamp_, writer_fp_);
}

//-----------------------------------------------------------
// Implementation of UserConsistency.
//-----------------------------------------------------------
void UserConsistency::WaitSignal() {
    // For a user process, user read the sigal from parameter fifo and
    // judge whether we can doing the work for next iteration.
    while (true) {
        int timestamp_of_parameter = FifoReadNum(reader_fp_);
        if(Judge()) break;
    }
}

void UserConsistency::IncreaseSignal() {
    // For a user process, user write to local data to in-memory file
    // and then increase the timestamp and write it to fifo. 
    WriteNum(++timestamp_, writer_fp_);
}

} // namespace brook
