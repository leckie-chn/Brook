// Copyright 2014 PKU-Cloud
// Author: Chao Ma (mctt90@gmail.com)
//
#include "src/sorted_buffer/sorted_buffer_iterator.h"

#include "gtest/gtest.h"

#include "src/base/common.h"
#include "src/base/varint32.h"
#include "src/sorted_buffer/sorted_buffer.h"

namespace sorted_buffer {

TEST(SortedBufferIteratorTest, SortedBufferIterator) {
    // The following code snippet that generates a series of two disk
    // block files are copied from sorted_buffer_test.cc
    //
    static const std::string kTmpFilebase("/tmp/testSortedBufferIterator");
    static const int kInMemBufferSize = 40; // Can hold two key-value pairs
    static const std::string kSomeStrings[] = {
        "applee", "banana", "applee", "papaya"
    };
    static const std::string kValue("123456");
    {
        SortedBuffer buffer(kTmpFilebase, kInMemBufferSize, 0, 0);
        for (int k = 0; k < sizeof(kSomeStrings)/sizeof(kSomeStrings[0]); ++k) {
            buffer.Insert(kSomeStrings[k], kValue);
        }
        buffer.Flush();
        EXPECT_EQ(buffer.NumFiles(), 2);
    }
    
    int i = 0;
    SortedBufferIterator iter(kTmpFilebase, 0, 0, 2);
    while (iter.HasNext()) {
        EXPECT_EQ(iter.key(), kSomeStrings[i]);
        EXPECT_EQ(iter.value(), kValue);
        i++;
    }
    iter.Clear();
}

} // namespace sorted_buffer
