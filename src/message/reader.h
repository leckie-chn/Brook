// Copyright 2015 PKU-Cloud.
// Author : Chao Ma (mctt90@gmail.com)
//
// Define the interface of Reader and two standard readers : 
// TextReader and ProtoRecordReader.
//
#ifndef MESSAGE_READER_H_
#define MESSAGE_READER_H_

#include <stdio.h>
#include <string>

#include "src/util/class_register.h"
#include "src/util/scoped_ptr.h"

#include "src/message/message.pb.h"

namespace brook {

//-------------------------------------------------------------------
// The interface implemented by 'real' readers.
//-------------------------------------------------------------------
class Reader {
public:
    Reader() { input_stream_ = NULL; }
    virtual ~Reader() { Close(); }

    virtual void Open(const std::string& source_name);
    virtual void Close();

    // Returns false to indicate that the current read failed and no
    // further reading operations should be performed.
    virtual bool Read(DoubleMessage&) = 0;
    virtual bool Read(FloatMessage&) = 0;
    virtual bool Read(IntMessage&) = 0;
    virtual bool Read(VectorMessage&) = 0;

protected:
    std::string input_filename_;
    FILE* input_stream_;
};

//-------------------------------------------------------------------
// Read each records as a line in a text file.
//-------------------------------------------------------------------
class TextReader : public Reader {
public:
    TextReader();
    virtual bool Read(DoubleMessage&);
    virtual bool Read(FloatMessage&);
    virtual bool Read(IntMessage&);
    virtual bool Read(VectorMessage&);

private:
    scoped_array<char> line_;
};

//-------------------------------------------------------------------
// Read each record as a binary format.
//-------------------------------------------------------------------
class ProtoRecordReader : public Reader {
public:
    virtual bool Read(DoubleMessage&);
    virtual bool Read(FloatMessage&);
    virtual bool Read(IntMessage&);
    virtual bool Read(VectorMessage&);
};

CLASS_REGISTER_DEFINE_REGISTRY(brook_reader_registry, Reader);

#define REGISTER_READER(format_name, reader_name)         \
        CLASS_REGISTER_OBJECT_CREATOR(                    \
            brook_reader_registry,                        \
            Reader,                                       \
            format_name,                                  \
            reader_name)

#define CREATE_READER(format_name)                        \
        CLASS_REGISTER_CREATE_OBJECT(                     \
            brook_reader_registry,                        \
            format_name)

} // namespace brook

#endif // MESSAGE_READER_H_
