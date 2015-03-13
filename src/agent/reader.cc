// Copyright : 2015 PKU-Cloud.
// Author: Chao Ma (mctt90@gmail.com)
//
#include "src/agent/reader.h"

#include <stdio.h>
#include <string.h>

#include "src/base/common.h"
#include "src/base/file_util.h"
#include "src/strutil/stringprintf.h"

namespace brook {

const int kDefaultMaxInputLineLength = 16 * 1024; // 16 KB

typedef std::vector<std::string> StringVector;

//-------------------------------------------------------------
// Implementation of Reader
//-------------------------------------------------------------
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

//-------------------------------------------------------------
// Implementation of TextReader
//-------------------------------------------------------------
TextReader::TextReader() {
    try {
        CHECK_LT(1, kDefaultMaxInputLineLength);
        line_.reset(new char[kDefaultMaxInputLineLength]);
    } catch(std::bad_alloc&) {
        LOG(FATAL) << "Cannot allocate line input buffer.";
    }
}

bool TextReader::Read(SendMessage* sm) {
    if (input_stream_ == NULL) {
        return false;
    }

    if (fgets(line_.get(), kDefaultMaxInputLineLength, input_stream_) 
        == NULL) {
        return false; // Either ferror or feof. Anyway, returns false to
                      // notify the caller no futher reading operations.
    }

    int read_size = strlen(line_.get());
    if (line_[read_size - 1] == '\n') {
        line_[read_size - 1] = '\0';
    }
    line_value_->assign(line_.get());
    SplitStringUsing(line_value_, "\t", &sv_);
    sm->mutable_list->Clear();
    std::istringstream parser;
    for (int i = 0 ; i < sv.size() ; i++) {
        parser.str(sv[i]);
        if (i == 0) {
            int i_index;
            parser >> i_index;
            sm->set_index(i_index);
        }
        else {
            double d_value;
            parser >> d_value;
            sm->mutable_list()->add_value(d_value);
        }
    }
    return true;
}

} // namespace brook
