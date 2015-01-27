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
#include <stdio.h>
#include <string>
#include <iostream>

#include "gtest/gtest.h"

#include "src/base/common.h"
#include "src/mrml/protofile.h"
#include "src/mrml/protofile.pb.h"

namespace brook {
namespace protofile {


using namespace std;    
using std::string;

static const char* kTestKey = "a key";
static const char* kTestValue = "a value";

static void CheckWriteReadConsistency(const string& filename) {
  KeyValuePair pair;
  pair.set_key(kTestKey);
  pair.set_value(kTestValue);

  FILE* file = fopen(filename.c_str(), "w");
  CHECK(file != NULL);
  WriteRecord(file, kTestKey, kTestValue);
  WriteRecord(file, kTestKey, pair);
  fclose(file);

  cout << "here1----------------" << endl;

  CHECK((file = fopen(filename.c_str(), "r")) != NULL);
  string key, value;
  CHECK(ReadRecord(file, &key, &value));
  EXPECT_EQ(key, kTestKey);
  EXPECT_EQ(value, kTestValue);

  cout << "here2----------------" << endl;

  pair.Clear();
  CHECK(ReadRecord(file, &key, &pair));
  EXPECT_EQ(pair.key(), kTestKey);
  EXPECT_EQ(pair.value(), kTestValue);

  cout << "here3----------------" << endl;

  //EXPECT_TRUE(!ReadRecord(file, &key, &value));

  cout << "here4----------------" << endl;
}

}  // namespace protofile
}  // namespace brook

TEST(ProtofileTest, LocalRecordIO) {
  static const char* kFilename = "/tmp/ProtofileTestLocalRecordIO";
  brook::protofile::CheckWriteReadConsistency(kFilename);
}
