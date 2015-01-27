// Copyright 2015 PKU-Cloud.
// Author: Chao Ma (mctt90@gmail.com)
//
// Wrappers for iostream, use stdin and stdout if filename is "-"
//
#ifndef BASE_STREAM_WRAPPER_H_
#define BASE_STREAM_WRAPPER_H_

#include <cstring>
#include <fstream>
#include <iostream>

namespace stream_wrapper {

class ostream_wrapper {
public:
    std::ostream &operator*() const { return *output_stream_; }
    std::ostream *operator->() const { return output_stream_; }

    explicit ostream_wrapper(const char* filename);
    virtual ~ostream_wrapper();

private:
    std::ostream* output_stream_;
};

class istream_wrapper {
public:
    std::istream &operator*() const { return *input_stream_; }
    std::istream *operator->() const { return input_stream_; }

    explicit istream_wrapper(const char* filename);
    virtual ~istream_wrapper();

private:
    std::istream* input_stream_;
};

} // stream_wrapper

#endif // BASE_STREAM_WRAPPER_H_
