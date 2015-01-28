// Copyright 2014 PKU-Cloud.
// Author: Chao Ma (mctt90@gmail.com)
//
#ifndef SORTED_BUFFER_SORTED_BUFFER_ITERATOR_H_
#define SORTED_BUFFER_SORTED_BUFFER_ITERATOR_H_

#include <string>
#include <vector>

#include "src/base/common.h"
#include "src/sorted_buffer/memory_piece.h"

namespace sorted_buffer {

typedef std::vector<FILE*> FileList;

class SortedBufferIterator {
public:
    SortedBufferIterator(const std::string& filebase, int timestamp,
                         int worker_id, int num_files);

    ~SortedBufferIterator() {}

    bool HasNext();
    const std::string& key();
    const std::string& value();
    void Clear();

private:

    void Initialize(const std::string& filebase,
                    int timestamp,
                    int worker_id,
                    int num_files);

    FileList file_list_;
    int current_file_index_;
    std::string current_key_;
    std::string current_value_;

};

} // namespace sorted_buffer

#endif // SORTED_BUFFER_SORTED_BUFFER_ITERATOR_H_
