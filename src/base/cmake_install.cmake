# Install script for directory: /Users/alex/brook/src/base

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "/Users/alex/brook-install")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/bin/base" TYPE STATIC_LIBRARY FILES "/Users/alex/brook/src/base/libbase.a")
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/base/libbase.a" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/base/libbase.a")
    execute_process(COMMAND "/usr/bin/ranlib" "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/base/libbase.a")
  endif()
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/base" TYPE FILE FILES
    "/Users/alex/brook/src/base/class_register.h"
    "/Users/alex/brook/src/base/class_register_test_helper.h"
    "/Users/alex/brook/src/base/common.h"
    "/Users/alex/brook/src/base/cvector.h"
    "/Users/alex/brook/src/base/file_util.h"
    "/Users/alex/brook/src/base/filepattern.h"
    "/Users/alex/brook/src/base/logging.h"
    "/Users/alex/brook/src/base/random.h"
    "/Users/alex/brook/src/base/scoped_ptr.h"
    "/Users/alex/brook/src/base/stdint_msvc.h"
    "/Users/alex/brook/src/base/stl-util.h"
    "/Users/alex/brook/src/base/stream_wrapper.h"
    "/Users/alex/brook/src/base/varint32.h"
    )
endif()

