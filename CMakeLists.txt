# Copyright 2014 PKU-Cloud.
# Author: Chao Ma (mctt90@gmail.com)
#
# This is the root CMakeLists.txt file in the brook project,
# which build all subdirectories (packages) in the order of
# inter-package dependence. You might not have ``check-out`` access
# to all these packages. If so, please just comment out lines
# referring to packages that you cannot access. But please confirm
# with the source management administrator that once you hace access
# to package A, you must also have access to all packages on which A
# depends.
#
# Before you can build brook, you need to build and install 
# dependent libraries following
#
# http://
# 
# This wiki page assumes you installed all 3rd-party libraries into a
# derectory named /home/you/3rd-party. You need to use that directory
# to replace the directory in the following variable setting:
#
# set(THIRD_PARTY_DIR "/Users/alex/3rd-party")
#
# Now, you can build the brook using following commands:
#
# $> mkdir build
# $> cd build
# $> cmake ../brook
# $> make
#
# Thus you check out the brook project and build it in a
# outsied directory ``build``. If you want further to install the built
# project, you can modify the default installation directory:
#
# set(CMAKE_INSTALL_PREFIX "/home/alex/brook-install")
#
# and type the command
#
# $> make install
#
# If you want to use distcc for a distributed build, substitute above
# command
# cmake ../brook
# by
# CC=distcc cmake ../brook
#
project ("brook")

cmake_minimum_required(VERSION 2.8) # Required 2.8 for protobuf support.

#----------------------------------------------------------------------------
# Add protobuf compilation support
#----------------------------------------------------------------------------
include("FindProtobuf")
find_package(Protobuf REQUIRED)

#----------------------------------------------------------------------------
# Take almost all warning;
# Take warnings as errors;
# Do not generate debug symbols;
# Optimization level O2;
#----------------------------------------------------------------------------
add_definitions(" -Wall -Wno-sign-compare -O2 ")

#----------------------------------------------------------------------------
# Declare where out project will be installed.
#----------------------------------------------------------------------------
#set(CMAKE_INSTALL_PREFIX "/home/root/brook-install")
set(CMAKE_INSTALL_PREFIX "/Users/alex/brook-install")
#----------------------------------------------------------------------------
# Ensure executables are statically linked with libraries.
#----------------------------------------------------------------------------
if(NOT ${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
    set(CMAKE_EXE_LINKER_FLAGS "-static -static-libgcc")
endif()

#----------------------------------------------------------------------------
# Set the include paths and library paths.
#
# Brook depends on the following thirdparty libraries:
#
# - boost
# - gflags
# - protobuf
# - mpich2
#
# You can install them using package management tools on your system,
# or build them from source by yourself. In either way, you need to
# tell where these libraries were installed. For example, if you
# build all libraries and install them to /home/alex/3rd-party, you
# might need the following commands:
#
#  set(THIRD_PARTY_DIR "/home/alex/3rd-party")
#  set(BOOST_DIR "${THIRD_PARTY_DIR}/boost")
#  set(GFLAGS_DIR "${THIRD_PARTY_DIR}/gflags")
#
#  include_directories(
#    "${BOOST_DIR}/include"
#    "${GFLAGS_DIR}/include"
#  )
#
#  link_directories(
#    "${BOOST_DIR}/lib"
#    "${GFLAGS_DIR}/lib"
#  )
#
# On MacOS x, Homebrew installs header files to /usr/local/include and
# libraries to /usr/local/lib.
#
# Brook uses googletest framework for unit testing. As it is 
# not recommanded to build googletest as a system-wide library, we
# must import googletest into our source tree before building brook.
#
# 1. Download or checkout googletest code from code.google.com/p/googletest.
# 2. Create a symbolic link named 'src/gtest' pointing to gooletest code.
#------------------------------------------------------------------------------
# set(THIRD_PARTY_DIR "/home/root/3rd-party/")
# set(BOOST_DIR "${THIRD_PARTY_DIR}/boost")
# set(GFLAGS_DIR "${THIRD_PARTY_DIR}/gflags")
# set(PROTOBUF_DIR "${THIRD_PARTY_DIR}/protobuf")
# set(MPICH2_DIR "${THIRD_PARTY_DIR}/mpich")
# set(OPENSSL_DIR "${THIRD_PARTY_DIR}/openssl")
# set(LIBSSH2_DIR "${THIRD_PARTY_DIR}/libssh2")

include_directories(
    "${PROJECT_SOURCE_DIR}"
    "${PROJECT_BINARY_DIR}"
    "${PROTOBUF_INCLUDE_DIRS}"
    "${PROJECT_SOURCE_DIR}/src/gtest/include"
    # "${BOOST_DIR}/include"
    # "${GFLAGS_DIR}/include"
    # "${PROTOBUF_DIR}/include"
    # "${MPICH2_DIR}/include"
    # "${OPENSSL_DIR}/include"
    # "${LIBSSH2_DIR}/include"
    "usr/local/include"
    )

link_directories(
    "${PROJECT_BINARY_DIR}/src/base"
    "${PROJECT_BINARY_DIR}/src/strutil"
    "${PROJECT_BINARY_DIR}/src/hash"
    "${PROJECT_BINARY_DIR}/src/agent"
    "${PROJECT_BINARY_DIR}/src/server"
    "${PROJECT_BINARY_DIR}/src/sorted_buffer"
    "${PROJECT_BINARY_DIR}/src/message"
    "${PROJECT_BINARY_DIR}/src/in_memory_store"
    # "${BOOST_DIR}/lib"
    # "${GFLAGS_DIR}/lib"
    # "${PROTOBUF_DIR}/lib"
    # "${MPICH2_DIR}/lib"
    "/usr/local/lib"
    )

#------------------------------------------------------------------------------
# Declare packages in paralgo project
#------------------------------------------------------------------------------
add_subdirectory(src/agent)
add_subdirectory(src/server)
add_subdirectory(src/base)
add_subdirectory(src/gtest)
add_subdirectory(src/strutil)
add_subdirectory(src/hash)
add_subdirectory(src/sorted_buffer)
add_subdirectory(src/message)
add_subdirectory(src/in_memory_store)
add_subdirectory(data)
