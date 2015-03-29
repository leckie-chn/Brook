// Copyright 2015 PKU-Cloud.
// Auhtor : Chao Ma (mctt90@gmail.com)
//
// Fifo is a wrapper for linux fifo mechanism.
//
#ifndef CONSISTENCY_FIFO_H_
#define CONSISTENCY_FIFO_H_

#include "src/util/common.h"
#include "src/util/logging.h"

#include <string>

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <fstream>

#define EVERYONE_CAN_READ_AND_WRITE 0666

namespace brook {

class Fifo {
public:

    Fifo(std::string filename) : file_name_(filename) {
        unlink(file_name_.c_str()); // Ensure close the pre-created file.
        if(mkfifo(file_name_.c_str(), EVERYONE_CAN_READ_AND_WRITE) != 0) {
            LOG(FATAL) << "Create fifo file failed.";
        }
        file_.open(file_name_.c_str());
        if(!file_.is_open()) {
            LOG(FATAL) << "Open fifo file error.";
        }
    }
    ~Fifo() { 
        file_.close();   
        unlink(file_name_.c_str());
    }

    int ReadNum();
    void WriteNum(int num);

private:
    std::string file_name_;
    std::fstream file_;
};

} // namespace brook


#endif // CONSISTENCY_FIFO_H_
