// Copyright 2014 PKU-Cloud.
// Author: Chao Ma (mctt90@gmail.com)
//
// Protofile is a legacy file format from MRML. In MRML, it is called
// "RecordIO", however, as it differs completely with the well-know
// "RecordIO" developed in Google, we rename it "protofile" in this system.
//
// In general, a protofile is a binary file of records, where each record 
// consists of a 4-bytes (uint32) record size and a serialized keyValuePair
// proto message.
//
#ifndef MAPREDUCE_PROTOFILE_H_
#define MAPREDUCE_PROTOFILE_H_

#include <stdio.h>

#include <string>

namespace google {
namespace protobuf {
class Message;
}
}

namespace brook {
namespace protofile {

bool ReadRecord(FILE* input,
                std::string* key,
                std::string* value);

bool ReadRecord(FILE* input,
                std::string* key,
                ::google::protobuf::Message* value);

bool ReadRecord(FILE* input,
                ::google::protobuf::Message* key,
                std::string* value);

bool ReadRecord(FILE* input,
                ::google::protobuf::Message* key,
                ::google::protobuf::Message* value);

bool WriteRecord(FILE* output,
                 const std::string& key,
                 const std::string& value);

bool WriteRecord(FILE* output,
                 const std::string& key,
                 const ::google::protobuf::Message& value);

bool WriteRecord(FILE* output,
                 const ::google::protobuf::Message& key,
                 const std::string& value);

bool WriteRecord(FILE* output,
                 const ::google::protobuf::Message& key,
                 const ::google::protobuf::Message& value);

} // namespace protofile
} // namespace brook

#endif // MAPREDUCE_PROTOFILE_H_
