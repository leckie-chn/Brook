// Copyright 2014 PKU-Cloud
// Author: Chao Ma (mctt90@gmail.com)
//
#include "src/sorted_buffer/sorted_buffer_iterator.h"

#include "src/base/varint32.h"
#include "src/sorted_buffer/memory_piece.h"
#include "src/sorted_buffer/sorted_buffer.h"
#include "src/strutil/stringprintf.h"

namespace sorted_buffer {

SortedBufferIterator::SortedBufferIterator(const std::string& filebase, int timestamp,
                                           int worker_id, int num_files)
    : current_file_index_(0)
{
    Initialize(filebase, timestamp, worker_id, num_files);
}

void SortedBufferIterator::Initialize(const std::string& filebase,
                                      int timestamp,
                                      int worker_id,
                                      int num_files)
{
    for (int i = 0 ; i < num_files ; i++) {
        std::string file_name = StringPrintf("%s-%d-%d-%d",
                                             filebase.c_str(),
                                             timestamp,
                                             worker_id, i);

        FILE *fp = fopen(file_name.c_str(), "r");
        if (fp == NULL) {
            LOG(FATAL) << "Cannot open file: "
                       << file_name;
        }
        file_list_.push_back(fp);
    }
}

bool SortedBufferIterator::HasNext() {

    if (ReadMemoryPiece(file_list_[current_file_index_], &current_key_) &&
        ReadMemoryPiece(file_list_[current_file_index_], &current_value_)) 
    {
        return true;
    }
    else {
        if (current_file_index_ == file_list_.size() - 1) {
            return false;
        } 
        else {
            current_file_index_++;
            return HasNext();
        }
    }
}

const std::string& SortedBufferIterator::key() {
    return current_key_;
}

const std::string& SortedBufferIterator::value() {
    return current_value_;
}    

void SortedBufferIterator::Clear() {
    for (FileList::iterator i = file_list_.begin(); i != file_list_.end(); ++i) {
        fclose((*i));
        // delete *i;
    }
    file_list_.clear();
}

} // namespace sorted_buffer
