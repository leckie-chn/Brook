// Copyright 2015 PKU-Cloud.
// Author : Chao Ma (mctt90@gmail.com)
//
#ifndef CONSISTENCY_CONSISTENCY_H_
#define CONSISTENCY_CONSISTENCY_H_

#include "src/consistency/fifo.h"

#include <vector>
#include <string>

namespace brook {

class Consistency {
public:
    Consistency(std::string reader, std::string writer) 
    : reader_filename_(uf), writer_filename_(pf) {
        reader_fp_ = OpenReadFifo(reader_filename_);
        writer_fp_ = OpenWriteFifo(writer_filename_);
        reader_count_ = 0;
        writer_count_ = 0;
    }

    virtual void Wait();
    virtual void Increase();
    virtual bool () = 0;

private:
    std::string reader_filename;
    std::string writer_filename_;
    int reader_fp_;
    int writer_fp_;
    int reader_count_;
    int writer_count_;
};

} // namespace brook

#endif // CONSISTENCY_CONSISTENCY_H_
