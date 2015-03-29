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

#define EVERYONE_CAN_READ_AND_WRITE 0666

namespace brook {

class Fifo {
public:

    Fifo(std::string filename, int flag) : file_name_(filename), flag_(flag) {
        unlink(file_name_.c_str()); // Ensure close the pre-created file.
        if(mkfifo(file_name_.c_str(), EVERYONE_CAN_READ_AND_WRITE) != 0) {
            LOG(FATAL) << "Create fifo file failed.";
        }
        file_hd_ = open(file_name_.c_str(), flag);
        if (file_hd_ == -1) {
            LOG(FATAL) << "Open fifo file error.";
        }
    }
    ~Fifo() { 
        close(file_hd_);
        unlink(file_name_.c_str());
    }

    int ReadNum();
    void WriteNum(int num);

private:
    std::string file_name_;
    int file_hd_;
    int flag_;


};

} // namespace brook


#endif // CONSISTENCY_FIFO_H_
