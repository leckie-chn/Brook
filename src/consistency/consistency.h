// Copyright 2015 PKU-Cloud.
// Author : Chao Ma (mctt90@gmail.com)
//
// AgentConsistency is the controller for the task synchronism. User can 
// implement various consistency model just by implementing the 
// Judge method.
// 
#ifndef CONSISTENCY_CONSISTENCY_H_
#define CONSISTENCY_CONSISTENCY_H_

#include "src/consistency/fifo.h"
#include "src/util/common.h"

#include <string>

namespace brook {

const int FILE_OPEN_ERROR = -1;

//-----------------------------------------------------------------
// The base class
//-----------------------------------------------------------------
class Consistency {
public:
    
    Consistency(std::string reader, std::string writer) 
    : reader_filename_(reader), writer_filename_(writer) {
        // Open fifo file
        reader_fp_ = OpenReadFifo(reader_filename_);
        CHECK_NE(reader_fp_, FILE_OPEN_ERROR);

        writer_fp_ = OpenWriteFifo(writer_filename_);
        CHECK_NE(reader_fp_, FILE_OPEN_ERROR);
    }

    virtual ~Consistency() { 
        // unlink the fifo file.
        DeleteFifo(reader_filename_);
        DeleteFifo(writer_filename_);
    }

    virtual void WaitSignal() = 0;        // Read the signal from fifo file.
    virtual void IncreaseSignal() = 0;    // Increase sigal and write to fifo file.

private:

    std::string reader_filename_;     // The filename of the reader file.
    std::string writer_filename_;     // The filename of the writer file.
    int reader_fp_;                   // The file pointer of the reader file.
    int writer_fp_;                   // The file pointer of the writer file.

    virtual bool Judge() = 0;
};

class AgentConsistency : public Consistency {
public:
    virtual void WaitSignal();
    virtual void IncreaseSignal();

private:
    virtual bool Judge();
};


} // namespace brook

#endif // CONSISTENCY_CONSISTENCY_H_
