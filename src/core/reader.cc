// Copyright 2015 PKU-Cloud.
// Author : Chao Ma (mctt90@gmail.com)
//
#include "src/core/reader.h"

#include <stdio.h>
#include <string.h>

#include "src/base/common.h"
#include "src/base/file_util.h"
#include "src/core/message.h"
#include "src/strutil/stringprintf.h"
#include "src/strutil/split_string.h"

const int kDefaultMaxInputLineLength = 1 * 1024; // 1 KB

namespace brook {

CLASS_REGISTER_IMPLEMENT_REGISTRY(brook_reader_registry, Reader);
REGISTER_READER("text", TextReader);
REGISTER_READER("protofile", ProtoRecordReader);

//--------------------------------------------------------------------------
// Implementation of Reader
//--------------------------------------------------------------------------
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

static std::string str_line;
static std::vector<std::string> str_list;
//--------------------------------------------------------------------------
// Implementation of TextReader
//--------------------------------------------------------------------------
TextReader::TextReader() {
    try {
        CHECK_LT(1, kDefaultMaxInputLineLength);
        line_.reset(new char[kDefaultMaxInputLineLength]);
    } catch (std::bad_alloc&) {
        LOG(FATAL) << "Cannot allocate line input buffer.";
    }
}

bool Text::Read(Message* message) {
    if (input_stream_ == NULL) {
        return false;
    }

    if (fgets(line_.get(), kDefaultMaxInputLineLength, input_stream_)
            == NULL) {
        return false; // Either ferror or feof, Anyway, returns false to
                      // notify the caller no further reading operations.
    }

    int read_size = strlen(line_.get());
    if (line_[read_size - 1] != '\n') {
        LOG(FATAL) << "Read a too long line.";
    } 

    if (line_[read_size - 1] == '\n') {
        line_[read_size - 1] == '\0';
        if (read_size > 1 & line_[read_size - 2] == '\r') { // Handle DOS
                                                            // text format.
             line_[read_size - 2] = '\0';
        }
    }
    str_line->assign(line_.get());
    SplitStringUsing(str_line, &str_list);
    // Using string to set message.
    message->SetKeyValueUsingString(str_list[0], str_list[1]);   
}

} // namespace brook
