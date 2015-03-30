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

        // The first iterartion.
        last_reader_count_ = 0;
        last_writer_count_ = 0;
        cur_reader_count_ = 0;
        cur_writer_count_ = 0;
    }

    virtual ~Consistency() { 
        DeleteFifo(reader_filename_);
        DeleteFifo(writer_filename_);
    }

    virtual void Wait();
    virtual void Increase();
    virtual bool Judge() = 0; 

private:

    std::string reader_filename_;     // The filename of the reader file.
    std::string writer_filename_;     // The filename of the writer file.
    int reader_fp_;                   // The file pointer of the reader file.
    int writer_fp_;                   // The file pointer of the writer file.

    int cur_reader_count_;            
    int cur_writer_count_;
    int last_reader_count_;
    int last_writer_count_;
};


//-----------------------------------------------------------------
// Bulk Synchronous Parallel. (BSP)
//-----------------------------------------------------------------
class BSP : public Consistency {
public:
    virtual bool Judge();
};

//-----------------------------------------------------------------
// Asychronous.
//-----------------------------------------------------------------
class Asychronous : public Consistency {
public:
    virtual bool Judge();
};  

//-----------------------------------------------------------------
// Stale Synchronous Parallel. (SSP)
//-----------------------------------------------------------------
class SSP : public Consistency {
public:
    SSP(std::string reader, std::string writer, int bounded) 
    : Consistency(reader, writer), bounded_staleness_(bounded) {}

    virtual bool Judge();

private:
    int bounded_staleness_;
};

} // namespace brook

#endif // CONSISTENCY_CONSISTENCY_H_
