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
    
    Consistency(int reader, int writer) 
    : reader_fp_(reader), writer_fp_(writer) {
        timestamp_ = 0;
    }

    ~Consistency() {
        CloseFifo(reader_fp_);
        CloseFifo(writer_fp_);
    }

    virtual void WaitSignal() = 0;        // Read the signal from fifo file.
    virtual void IncreaseSignal();        // Increase sigal and write to fifo file.
    virtual int GetTimeStamp() const { return timestamp_; }

protected:

    int reader_fp_;                   // The file pointer of the reader file.
    int writer_fp_;                   // The file pointer of the writer file.

    int timestamp_;                   // current iteration number.
};

//-------------------------------------------------------------
// UserConsistency.
//-------------------------------------------------------------
class UserConsistency : public Consistency {
public:
    UserConsistency(int reader, int writer)
    : Consistency(reader, writer) {
        last_timestamp_ = 0;
    }

    virtual void WaitSignal();

protected:
    virtual bool Judge() = 0;

    int last_timestamp_;
};


//-------------------------------------------------------------
// AgentConsistency.
//-------------------------------------------------------------
class AgentConsistency : public Consistency {
public:
    AgentConsistency(int reader, int writer)
    : Consistency(reader, writer) {}

    virtual void WaitSignal();
};

//-------------------------------------------------------------
// Bulk synchronism parallel. (BSP)
//-------------------------------------------------------------
class BSP : public UserConsistency {
public:
    BSP(int reader, int writer)
    : UserConsistency(reader, writer) {}

protected:
    bool Judge();
};

//-------------------------------------------------------------
// Asynchronism.
//-------------------------------------------------------------
class Asy : public UserConsistency {
public:
    Asy(int reader, int writer)
    : UserConsistency(reader, writer) {}

protected:
    bool Judge();
};

//-------------------------------------------------------------
// Stale synchronism parallel. (SSP)
//-------------------------------------------------------------
class SSP : public UserConsistency {
public:
    SSP(int reader, int writer, int bounded) 
    : UserConsistency(reader, writer), 
      bounded_staleness_(bounded) {}

protected:
    int bounded_staleness_;

    bool Judge();
};

} // namespace brook

#endif // CONSISTENCY_CONSISTENCY_H_
