// Copyright 2015 PKU-Cloud.
// Author : Chao Ma (mctt90@gmail.com)
//
#include "src/message/reader.h"

#include <stdio.h>
#include <string.h>

#include "src/util/common.h"
#include "src/util/file_util.h"
#include "src/util/stringprintf.h"
#include "src/util/split_string.h"

const int kDefaultMaxInputLineLength = 16 * 1024; // 16KB

namespace brook {

CLASS_REGISTER_IMPLEMENT_REGISTRY(brook_reader_registry, Reader);
REGISTER_READER("test", TextReader);
REGISTER_READER("protofile", ProtoRecordReader);

//-------------------------------------------------------------------------
// Implementation of Reader
//-------------------------------------------------------------------------
void Reader::Open(const std::string& source_name) {
    Close(); // Ensure to close pre-opened file.
    input_filename_ = source_name;
    input_stream_ = OpenFileOrDie(source_name.c_str(), "r");
}

void Reader::Close() {
    if (input_stream_ != NULL) {
        fclose(input_stream_);
        input_stream_ = NULL;
    }
}

//-------------------------------------------------------------------------
// Implementation of TextReader
//-------------------------------------------------------------------------
TextReader::TextReader() {
    try {
        line_.reset(new char[kDefaultMaxInputLineLength]);
        current_index_ = -1;
    } catch(std::bad_alloc&) {
        LOG(FATAL) << "Cannot allocate line input buffer.";
    }
}

bool get_record() {
    if (input_stream_ == NULL) {
        return false;
    }

    if (fgets(line_.get(), kDefaultMaxInputLineLength, input_stream_)
            == NULL) {
        return false;   // Either ferror or feof. Anyway, returns flase to
                        // notify the caller no futher reading operations.
    }

    int read_size = strlen(line_.get());

    if (line_[read_size - 1] != '\n') {
        LOG(FATAL) << "Reading a too long line.";
    } else {
        line_[read_size - 1] = '\0';
        if (read_size > 1 && line_[read_size - 2] == '\r') {
            line_[read_size - 2] = '\0';  // Handle DOS
        }                                 // text format.
    }

    sv_.clear();
    str_line_.assign(line_.get());
    SplitStringUsing(str_line_, "\t", &sv_);

    return true;
}

bool TextReader::Read(DoubleMessage& msg) {
    while (true) {
        if (get_record()) {
            // parse the index
            parser_.clear();
            parser_ << sv_[0];
            uint64 index;
            parser_ >> index;
            // rebuild a new message
            if (current_index_ == -1 || current_index_ != index+1) {

            } else {
                
            }

        } 
    }
}

bool TextReader::Read(FloatMessage& msg) {

}

bool TextReader::Read(IntMessage& msg) {
    
}

bool TextReader::Read(VectorMessage& msg) {

}

} // namespace brook

