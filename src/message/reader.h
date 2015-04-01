// Copyright 2015 PKU-Cloud.
// Author : Chao Ma (mctt90@gmail.com)
//
// Define the interface of Reader and two standard readers : 
// TextReader and ProtoRecordReader.
//
// The message format is:
//
// ----------------------
// | HeaderMessage:     |
// |   1. worker_id     |
// |   2. start_index   |
// |                    |
// | list:              |
// |   0.32             |
// |   1.43             |
// |   .                |
// |   .                |
// |   .                |
// |   2.12             |
// ----------------------
//
#ifndef MESSAGE_READER_H_
#define MESSAGE_READER_H_

#include <stdio.h>
#include <string>
#include <vector>
#include <sstream>

#include "src/util/class_register.h"
#include "src/util/scoped_ptr.h"
#include "src/util/common.h"
#include "src/message/partition.h"
#include "src/message/message.pb.h"

namespace brook {

typedef std::vector<std::string> StringVector;

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
    // virtual bool Read(FloatMessage&) = 0;
    // virtual bool Read(IntMessage&) = 0;
    // virtual bool Read(VectorMessage&) = 0;

protected:
    std::string input_filename_;
    FILE* input_stream_;
    std::stringstream parser_;
    
    void parseInt(std::string&, uint64*);
    void parseDouble(std::string&, double*);
    void parseFloat(std::string&, float*);
};

//-------------------------------------------------------------------
// Read each records as a line in a text file.
//-------------------------------------------------------------------
class TextReader : public Reader {
public:
    TextReader(Partition);
    virtual bool Read(DoubleMessage&);
    // virtual bool Read(FloatMessage&);
    // virtual bool Read(IntMessage&);
    // virtual bool Read(VectorMessage&);
    virtual void OpenFile(const std::string& source_name);

private:
    scoped_array<char> line_;            // input line buffer
    bool get_record();                   // get the index and value in string format
    std::string str_line_;               // the container to hold a string line
    StringVector sv_;                    // the container to hold the splited contents
    Partition partition_;    

    bool NotInSameShard(uint64 index, uint64 next_index);
};

//-------------------------------------------------------------------
// Read each record as a binary format.
//-------------------------------------------------------------------
class ProtoRecordReader : public Reader {
public:
    virtual bool Read(DoubleMessage&);
    // virtual bool Read(FloatMessage&);
    // virtual bool Read(IntMessage&);
    // virtual bool Read(VectorMessage&);
};

/*
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

*/

} // namespace brook

#endif // MESSAGE_READER_H_
