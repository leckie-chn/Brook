/*
This program is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 2 of the License, or (at
your option) any later version.

This program is distributed in the hope that it will be useful, but
WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA
02110-1301, USA.
*/
// Copyright 2014 PKU-Cloud.
// Author: Chao Ma (mctt90@gmail.com)
//
#include "src/sorted_buffer/sorted_buffer.h"

#include <stdio.h>
#include <string.h>
#include <algorithm>

#include "src/base/common.h"
#include "src/base/varint32.h"
#include "src/strutil/stringprintf.h"
#include "src/sorted_buffer/sorted_buffer_iterator.h"

namespace sorted_buffer {

/*static*/
std::string SortedBuffer::SortedFilename(const std::string filebase,
                                         int index,
                                         int timestamp,
                                         int worker_id)
{
    return StringPrintf("%s-%d-%d-%d", filebase.c_str(), timestamp,
                                       worker_id, index);
}

SortedBuffer::SortedBuffer(const std::string& filebase,
                           int in_memory_buffer_size,
                           int timestamp,
                           int worker_id)
    : filebase_(filebase),
      allocator_(new NaiveMemoryAllocator(in_memory_buffer_size)),
      timestamp_(timestamp),
      worker_id_(worker_id)
{
    count_files_ = 0;
    CHECK(allocator_->IsInitialized());  // Ensure the memory pool is allocated.
}

void SortedBuffer::Insert(const std::string& key,
                               const std::string& value) {
  CHECK_LE(0, key.size());
  CHECK_LE(0, value.size());

  if (!allocator_->Have(key.size(), value.size())) {
    Flush();
    if (!allocator_->Have(key.size(), value.size())) {
      LOG(FATAL) << "The memory pool has insufficient space to hold incoming "
                 << "key-value pair: " << key << " : " << value;
    }
  }
  MemoryPiece key_piece;
  CHECK(allocator_->Allocate(key.size(), &key_piece));
  memcpy(key_piece.Data(), key.data(), key.size());

  MemoryPiece value_piece;
  CHECK(allocator_->Allocate(value.size(), &value_piece));
  memcpy(value_piece.Data(), value.data(), value.size());

  key_value_list_.push_back(KeyValuePair(key_piece, value_piece));
}

bool SortedBuffer::KeyValuePairLessThan(const KeyValuePair& x,
                                             const KeyValuePair& y) {
  return MemoryPieceLessThan()(x.key, y.key);
}

bool SortedBuffer::KeyValuePairEqual(const KeyValuePair& x,
                                          const KeyValuePair& y) {
  return MemoryPieceEqual(x.key, y.key);
}

void SortedBuffer::Flush() {
    if (!allocator_->IsInitialized() || allocator_->AllocatedSize() == 0)
        return;

    FILE* output = fopen(SortedFilename(filebase_, count_files_,
                                        timestamp_, worker_id_).c_str(), "w+");
    if (output == NULL) {
        LOG(FATAL) << "Cannot open disk swap file: "
                   << SortedFilename(filebase_, count_files_,
                                     timestamp_, worker_id_);
    }

    ++count_files_;
  
    int length = key_value_list_.size();
    for (int i = 0 ; i < length ; i++) {
        WriteMemoryPiece(output, key_value_list_[i].key);
        WriteMemoryPiece(output, key_value_list_[i].value);
    }

    fclose(output);
    key_value_list_.clear();
    allocator_->Reset();
}

SortedBufferIterator* SortedBuffer::CreateIterator() const {
  if (allocator_->AllocatedSize() > 0) {
    LOG(FATAL) << "You must invoke Flush before CreateIterator.";
  }
  return new SortedBufferIterator(filebase_, timestamp_, 
                                  worker_id_, count_files_);
}

void SortedBuffer::RemoveBufferFiles() const {
    /*
  if (allocator_->AllocatedSize() > 0) {
    LOG(FATAL) << "You must invoke Flush before RemoveBufferFiles.";
  }
  for (int i = 0; i < count_files_; ++i) {
    std::string filename = SortedFilename(filebase_, i);
    LOG(INFO) << "Removing : " << filename;
    if (remove(filename.c_str()) < 0) {
      LOG(ERROR) << "Cannot remove file: " << filename;
    }
  }
  */
}

}  // namespace sorted_buffer
