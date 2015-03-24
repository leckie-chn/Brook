// Copyright 2015 PKU-Cloud.
// Author : Chao Ma (mctt90@gmail.com)
//
#include "src/message/reader.h"

#include <stdio.h>
#include <string.h>

#include "src/util/common.h"
#include "src/util/file_util.h"
#include "src/util/stringprintf.h"

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


} // namespace brook

