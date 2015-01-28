// Copyright 2014 PKU-Cloud
// Author: Chao Ma (mctt90@gmail.com)
//
// NaiveMemoryAllocator implements a simple memory allocator, which
// allocates a big memory block during initialization, and 
// successively allocates variable-length pieces in the pool to
// applications. It does not support "free" nor "reallocate"; but
// supports "reset", which relclaims all allocated pieces for a new
// round of allocations. This allocator is designed for using in 
// ImMemoryBuffer.
//
// NOTE: the max size of each piece is 4G, so the size of each piece
//       can be represented by 4 bytes.
//
#ifndef SORTED_BUFFER_MEMORY_ALLOCATOR_H
#define SORTED_BUFFER_MEMORY_ALLOCATOR_H

#include "src/sorted_buffer/memory_piece.h"

namespace sorted_buffer {

class MemoryPiece;

class NaiveMemoryAllocator {
public:
    explicit NaiveMemoryAllocator(const int pool_size);
    ~NaiveMemoryAllocator();

    // Returns false for insufficiency memory
    bool Allocate(PieceSize size, MemoryPiece* piece);
    // Check if there is sufficient memory to hold a string.
    bool Have(PieceSize length) const;
    // Check if there is sufficient memory to hold two strings.
    bool Have(PieceSize key_length, PieceSize value_length);
    // Reclaims all allocated blocks for the next round of allocations.
    void Reset();

    const char* Pool() { return pool_; } // For test only.
    size_t PoolSize() const { return pool_size_; }
    size_t AllocatedSize() const { return allocated_size_; }
    bool IsInitialized() const { return pool_ != NULL; }

private:
    char* pool_;
    size_t pool_size_;
    size_t allocated_size_;

    DISALLOW_COPY_AND_ASSIGN(NaiveMemoryAllocator);
};

} // namespace sorted_buffer

#endif // SORTED_BUFFER_MEMORY_ALLOCATOR_H
