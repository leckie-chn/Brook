// Copyright 2015 PKU-Cloud.
// Author : Chao Ma (mctt90@gmail.com)
//
// Consistency is the controller for the task synchronism. User can 
// implement various consistency model just by implementing the 
// Judge method.
// 
#ifndef CONSISTENCY_CONSISTENCY_H_
#define CONSISTENCY_CONSISTENCY_H_

#include "src/consistency/fifo.h"

#include <string>

namespace brook {

//-----------------------------------------------------------------
// The base class
//-----------------------------------------------------------------
class Consistency {
public:
    Consistency(std::string reader, std::string writer) 
    : reader_filename_(uf), writer_filename_(pf) {
        reader_fp_ = OpenReadFifo(reader_filename_);
        writer_fp_ = OpenWriteFifo(writer_filename_);
        reader_count_ = 0;
        writer_count_ = 0;
    }

    virtual ~Consistency() { 
        DeleteFifo(reader_filename_);
        DeleteFifo(writer_filename_);
    }

    virtual void Wait();
    virtual void Increase();
    virtual bool Judge() = 0; 

private:
    std::string reader_filename;
    std::string writer_filename_;
    int reader_fp_;
    int writer_fp_;
    int reader_count_;
    int writer_count_;
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
    virtual bool Judge();
};

} // namespace brook

#endif // CONSISTENCY_CONSISTENCY_H_
