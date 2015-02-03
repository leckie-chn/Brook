// Copyright 2015 PKU-Cloud.
// Author : Chao Ma (mctt990@gmail.com)
//
// Define the interface which is used for reading text or 
// proto record from data cache.
//
#ifndef CORE_READER_H_
#define CORE_READER_H_

#include <stdio.h>
#include <string>

#include "src/base/class_register.h"
#include "src/base/scoped_ptr.h"
#include "src/core/message.h"

namespace brook {

//-----------------------------------------------------------------------------
// The interface implemented by "real" readers.
//-----------------------------------------------------------------------------
class Reader {
public:
    Reader() { input_stream_ = NULL; }
    virtual ~Reader() { Close(); }

    virtual void Open(const std::string& source_name);
    virtual void Close();

    // Returns false to indicate that the current read failed and no
    // further reading operations should be performed.
    virtual bool Read(Message* message) = 0;

protected:
    std::string input_filename_;
    FILE* input_stream_;
};  

//-----------------------------------------------------------------------------
// Read each message record from the text file (disk-based or memory-based)
// Each record in a line is represented as: "key[space]value\n"
// The '\r' (if there is any) and '\n' at the end of a line are removed.
//-----------------------------------------------------------------------------
class TextReader : public Reader {
public:
    TextReader();
    virtual bool Read(Message* message);
private:
    scoped_array<char> line_;
};

CLASS_REGISTER_DEFINE_REGISTRY(brook_reader_registry, Reader);

#define REGISTER_READER(format_name, reader_name)            \
    CLASS_REGISTER_OBJECT_CREATOR(                           \
        brook_reader_registry,                               \
        Reader,                                              \
        format_name,                                         \
        reader_name)

#define CREATE_READER(format_name)                           \
    CLASS_REGISTER_CREATE_OBJECT(                            \
        brook_reader_registry,                               \
        format_name)

} // namespace brook

#endif // CORE_READER_H_
