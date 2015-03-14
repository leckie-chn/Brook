// Copyright : 2015 PKU-Cloud.
// Author : Chao Ma (mctt90@gmail.com)
//
#include "src/agent/reader.h"

#include <string>
#include <fstream>

#include "src/message/message.pb.h"
#include "gtest/gtest.h"
#include "src/base/common.h"

namespace brook {

const std::string file_name("test_file");

void createATestFile(std::string file_name) {
    std::ofstream fout(file_name.c_str());
    std::string line("1\t0.324\t33.324\n");
    fout << line << line << line;
}

TEST(TextReader, read) {
    createATestFile(file_name);
    TextReader reader;
    reader.Open(file_name.c_str());
    SendMessage sm;
    while (true) {
        if (!reader.Read(&sm)) {
            break;
        }
        EXPECT_EQ(sm.index(), 1);
        EXPECT_EQ(sm.list().value_size(), 2);
        EXPECT_EQ(sm.list().value(0), 0.324);
        EXPECT_EQ(sm.list().value(1), 33.324);
    }
}

} // namespace brook
