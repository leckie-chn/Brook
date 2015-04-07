# Build Brook Project

Brook can be built on Linux, Mac OS X and FreeBSD, with GCC
(>=4.5.1) or Clang (>=3.0)

Brook depends on the following tools or libraries:

  * [CMake](http://www.cmake.org) is used to manage and build the
    project.
  * [Google Protocal Buffer](http://code.google.com/p/protobuf) is
    used for inter-worker communication and disk storage.
  * [GFlags](http://code.google.com/p/google-gflags/) is used to parse
    command line options.
  * [Google Test](http://code.google.com/p/googletest) is used to 
    write and run unit tests.
  * [Boost](http://www.boost.org/) helps developing multi-threading in
    asynchronous inter-worker communication and provides
    cross-platform filesystem support.
  * [mpich](http://www.mpich.org/) is used to high-performance message 
    passing.
  * [snappy](http://code.google.com/snappy/) is used to message 
    compressing.

# Install Building tools

## Install GCC or Clang
