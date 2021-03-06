// Copyright 2015 PKU-Cloud.
// Author : Chao Ma (mctt90@gmail.com)
//          Yan Ni (leckie.dove@gmail.com)
//
#include "src/message/reader.h"

#include <stdio.h>
#include <string.h>

#include "src/util/common.h"
#include "src/util/file_util.h"
#include "src/util/stringprintf.h"
#include "src/util/split_string.h"
#include "src/message/partition.h"
#include <boost/lexical_cast.hpp>

const int kDefaultMaxInputLineLength = 16 * 1024; // 16KB

namespace brook {

/*
CLASS_REGISTER_IMPLEMENT_REGISTRY(brook_reader_registry, Reader);
REGISTER_READER("text", TextReader);
REGISTER_READER("protofile", ProtoRecordReader);
*/

//-------------------------------------------------------------------------
// Implementation of Reader
//-------------------------------------------------------------------------
void Reader::Open(const std::string& source_name) {
    Close();          // Ensure to close pre-opened file.
    input_filename_ = source_name;
    input_stream_ = OpenFileOrDie(source_name.c_str(), "r");
}

void Reader::Close() {
    if (input_stream_ != NULL) {
        fclose(input_stream_);
        input_stream_ = NULL;
    }
}

void Reader::parseInt(std::string& str_value, uint64* num) {
    *num = boost::lexical_cast<int>(str_value.c_str());
}

void Reader::parseDouble(std::string& str_value, double* num) {
    *num = boost::lexical_cast<double>(str_value.c_str());
}

void Reader::parseFloat(std::string& str_value, float* num) {
    *num = boost::lexical_cast<float>(str_value.c_str());
}

//-------------------------------------------------------------------------
// Implementation of TextReader
//-------------------------------------------------------------------------
TextReader::TextReader(Partition *p) : partition_(p) {
    try {
        line_.reset(new char[kDefaultMaxInputLineLength]);
    } catch(std::bad_alloc&) {
        LOG(FATAL) << "Cannot allocate line input buffer.";
    }
    finally_ = false;
}

bool TextReader::NotInSameShard(uint64 index, uint64 next_index) {
    return partition_->Shard(index) !=
           partition_->Shard(next_index);
}

void TextReader::OpenFile(const std::string& source_name) {
    Open(source_name);
    sv_.clear();
    parser_.clear();
    // Read the first record.
    if (!get_record()) {
        LOG(FATAL) << "Read file error.";
    }
}

bool TextReader::get_record() {
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

    str_line_.assign(line_.get());
    SplitStringUsing(str_line_, " ", &sv_);

    return true;
}

bool TextReader::Read(DoubleMessage& msg) {
    if (finally_) return false;
    // Get first record
    uint64 index = 0;
    parseInt(sv_[0], &index);
    HeadMessage *ptr_hm = msg.mutable_head();
    ptr_hm->set_start_index(index);
    double value = 0;
    parseDouble(sv_[1], &value);
    msg.add_list(value);
    // Insert new value
    while (true) {
        sv_.clear();
        if (!get_record()) {   // End of the file
            finally_ = true;
            return true;
        } else {
            uint64 next_index = 0;
            parseInt(sv_[0], &next_index);
            if (next_index != index + 1 || 
                NotInSameShard(next_index, index)) {
                return true;
            } else {
                index = next_index;
                double value = 0;
                parseDouble(sv_[1], &value);
                msg.add_list(value);
            }
        }
    }
}

} // namespace brook

