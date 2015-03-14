// Copyright : 2015 PKU-Cloud
// Author: Chao Ma (mctt90@gmail.com)
//
// Define the interface of Reader : TextReader
//
#ifndef AGENT_READER_H_
#define AGENT_READER_H_

#include <stdio.h>
#include <string>
#include <string.h>
#include <vector>
#include <sstream>

#include "src/base/common.h"
#include "src/base/file_util.h"
#include "src/strutil/stringprintf.h"
#include "src/base/scoped_ptr.h"
#include "src/message/message.pb.h"


namespace brook {

typedef std::vector<std::string> StringVector;

//-------------------------------------------------------------
// The interface implemented by "real" readers.
//-------------------------------------------------------------
class Reader {
public:
    Reader() { input_stream_ = NULL; }
    virtual ~Reader() { Close(); }

    virtual void Open(const std::string& source_name);
    virtual void Close();

    // Returns false to indicate that the current read failed and no
    // further reading operations should be performed.
    virtual bool Read(SendMessage* sm) = 0;

protected:
    std::string input_filename_;
    FILE* input_stream_;
};


//-------------------------------------------------------------
// Read each record as a line in a text file.
//-------------------------------------------------------------
class TextReader : public Reader {
public:
    TextReader();
    virtual bool Read(SendMessage* sm);
private:
    std::istringstream str_parser_;
    scoped_array<char> line_;
    int record_count_;
    std::string line_value_;
    StringVector sv_;
};


} // namespace brook

#endif // AGENT_READER_H_
