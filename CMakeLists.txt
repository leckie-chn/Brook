# Copyright : 2015 PKU-Cloud
# Author : Chao Ma (mctt90@gmail.com)
#
# This is the root CMakeLists.txt file in Brook project,
# which build all subdirectories (packages) in the order of
# inter-package dependence. You might not have "check-out" access
# to all these packages. If so, please just comment out lines
# referring to packages that you connot access. But please confirm
# with the source management administrator that once you have access
# to package A, you must also have access to all packages on which A
# depends.
#
# Before you can buld Brook, you need to build and install 
# dependent libraries following
#
#   Brook wiki
#
# This wiki page assume you installed all 3rd-party libraries into a 
# directory named /home/you/3rd-party. You need to use that directory
# to replace the directory in the following variable setting:
#
#  set(THIRD_PARTY_DIR "/Users/alex/3rd-party") 
#
# Now, you can build the Brook using the following commands:
#
#  $> mkdir build
#  $> cd build
#  $> cmake ../
#  $> make
#
# Thus you check out the Brook project and build it in a
# subdirectory "build". If you want further to install the built
# project, you can modify the default installation directory:
#
#  set(CMAKE_INSTALL_PREFIX "/home/public/brook")
#
# and type the command
#
#  $> make install
#
# If you want to use distcc for distributed build, substitute above
# comamd
#  cmake ../brook/
# by
# CC=distcc cmake ../brook/
# 
project ("Brook")

cmake_minimum_required(VERSION 2.8)  # Requires 2.8 for protobuf support.

#------------------------------------------------------------------------------------------------
# Add protobuf compilation support
#------------------------------------------------------------------------------------------------
include("FindProtobuf")
find_package(Protobuf REQUIRED)

#------------------------------------------------------------------------------------------------
# Do not generate debug symbols;
# Optimization level 2;
#------------------------------------------------------------------------------------------------
add_definitions(" -Wno-sign-compare -O2 ")

#------------------------------------------------------------------------------------------------
# Declare where our project will be installed.
#------------------------------------------------------------------------------------------------
# Linux:
#set(CMAKE_INSTALL_PREFIX "/root/brook-install")
# Mac:
set(CMAKE_INSTALL_PREFIX "/Users/alex/brook-install")

#------------------------------------------------------------------------------------------------
# Ensure executable are statically linked with libraries.
#------------------------------------------------------------------------------------------------
if (NOT ${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
    set(CMAKE_EXE_LINKER_FLAGS "-static -static-libgcc")
endif()

#------------------------------------------------------------------------------------------------
# Set include paths and library paths and library paths.
#
# Brook depends on the following thridparty libraries:
#
#  - boost
#  - gflags
#  - mpich
#  - gtest
#
# You can install them using package management tools on your system,
# or build them from source by yourself. In either way, you need to 
# tell where these libraries were installed. For example, if you 
# build all libraries and install them to /home/alex/3rd-party, you
# might need the following commands:
#
#  set(THIRD_PARTY_DIR "/home/alex/3rd-party")
#  set(BOOST_DIR "${THIRD_PARTY_DIR/boost}")
#  set(GFLAGS_DIR "${THIRD_PARTY_DIR/gflags}")
#  set(MPICH_DIR "${THIRD_PARTY_DIR}/mpich")
#
#  include_directories(
#   "${BOOST_DIR}/include"
#   "${GFLAGS_DIR}/include"
#   "${MPICH_DIR/include}"
#  )
#
#  link_directories(
#   "${BOOST_DIR}/lib"
#   "${GFLAGS_DIR}/lib"
#   "${LIBEVENT_DIR}/lib"
#  )
#
# On MacOS X, Homebrew installs header files to /usr/local/include and
# libraries to /usr/local/lib.
#
# Brook uses googletest framework for unit testing. As it is
# not recommened to build googletest as a system-wide library, we
# must import googletest into our source tree before building Brook.
#
#  1. Download or checkout googletest code.
#  2. Create a symbolic link named "src/gtest" pointing to googletest code.
#----------------------------------------------------------------------------------
# Linux:
# set(THIRD_PARTY_DIR "/root/3rd-party")
# Mac:
set(THIRD_PARTY_DIR "/Users/alex/3rd-party")
set(BOOST_DIR "${THIRD_PARTY_DIR}/boost")
set(GFLAGS_DIR "${THIRD_PARTY_DIR}/gflags")
set(MPICH_DIR "${THIRD_PARTY_DIR}/mpich")

include_directories(
    "${PROJECT_SOURCE_DIR}"
    "${PROJECT_SOURCE_DIR}/src/gtest/include"
    "${PROJECT_BINARY_DIR}"
    "${PROTOBUF_INCLUDE_DIRS}"
    "${BOOST_DIR}/include"
    "${MPICH_DIR}/include"
    "/usr/local/include" # Developping machine
    )

link_directories(
    "${PROJECT_BINARY_DIR}"
    "${BOOST_DIR}/lib"
    "${GFLAGS_DIR}/lib"
    "${MPICH_DIR}/lib"
    "/usr/local/lib"  # Developping machine
    )

#----------------------------------------------------------------------
# Decalre packages in brook project
#----------------------------------------------------------------------
add_subdirectory(src/util)
add_subdirectory(src/parameter)
add_subdirectory(src/message)
add_subdirectory(src/gtest)
