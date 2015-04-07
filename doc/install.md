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

Brook can be built using GCC or Clang.

  * On Cygwin, run `setup.exe` and install `gcc` and `binutils.`
  * On Debian / Ubuntu Linux, type the command `sudo apt-get install gcc binutils` to install GCC, or `sudo apt-get install clang` to install Clang.
  * On FreeBSD, type the command `sudo pkg_add -r clang` to install Clang. Note that since version 9.0, FreeBSD does not update GCC but relies completely on Clang.
  * On Mac OS X, install XCode gets you Clang.

## Install CMake

Brook need CMake with version >= 2.8.0 to compile Google Protocol Buffer definations.

To insatll CMake from binary packages:

  * On Cygwin, run `setup.exe` and insatll `cmake` .
  * On Debian / Ubuntu Linux, type the command `sudo apt-get install cmake`.
  * On FreeBSD, type the command `sudo pkg_add -r cmake`.
  * On Mac OS X, if you have [homebrew](http://brew.sh/) , you can use the command `brew install cmake`. You can also download binary or source package and insatll it manually.

## Install Protobuf

Brook requires protobuf with version >= 2.3.0

To install protobuf from binary packages:

  * On Debian / Ubuntu Linux, you can run `sudo apt-get install libprotobuf-dev libprotoc-dev`.
  * On FreeBSD, you can run `sudo pkg_add -r protobuf`.
  * On Mac OS X, you can run `brew install protobuf protobuf-c`.

Or, you can install protobuf from source code:

  1. Download source code package, say `protobuf-2.5.0.tar.bz2`, from http://code.google.com/p/protobuf
  2. You need to install protobuf into a standard place, e.g., `/usr/local/`, so that CMake can find the protoc compiler and the library:

        tar xjf protobuf-2.5.0.tar.bz2
        cd protobuf-2.5.0
        ./configure --disable-shared --enable-static
        make
        sudo make insatll

# Install Dependencies

If you want to build and run Brook on a single node, you can simply install dependent packages using package management tool on your system. For example, ON MacOS X, you can use
Homebrew:

        brew install gflags boost mpich snappy

Or, on FreeBSD,

        pkg_add -r gflags boost mpich snappy

However, if you want to use Brook on a cluster of computers, you might want to build dependencies manually from source code. You can build static dependent libraries, and build Brook 
program link to these dependencies satically. This saves you from being bithered by deploying a set of libraries and concerning their versions. The following sections shows how to build
dependent packages from source code.

## Install GFlags

  1. Download the source code package (e.g., `gflags-2.0.tar.gz`) from http://code.google.com/p/google-gflags
  2. Unpack the source code anywhere (e.g., `gflags-2.0`)
  3. You are free to install gflags anywhere (e.g., `/home/alex/3rd-party/gflags`):

        cd gflags-2.0
        ./configure --prefix=/home/alex/3rd-party/gflags-2.0 # if you want to use defualt buidl tool, or
        # CC==clang CXX==clang++ ./configure --prefix=/home/alex/3rd-party/gflags-2.0
        make && make install
        ln -2 /home/alex/3rd-party/gflags-2.0 /home/alex/3rd-party/gflags

## Install Boost

  1. 
