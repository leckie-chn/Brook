# Install script for directory: /Users/alex/brook/src/core

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
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/bin" TYPE EXECUTABLE FILES "/Users/alex/brook/src/core/brook_main")
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/brook_main" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/brook_main")
    execute_process(COMMAND /usr/bin/install_name_tool
      -delete_rpath "/Users/alex/brook/src/base"
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/brook_main")
    execute_process(COMMAND /usr/bin/install_name_tool
      -delete_rpath "/Users/alex/brook/src/strutil"
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/brook_main")
    execute_process(COMMAND /usr/bin/install_name_tool
      -delete_rpath "/Users/alex/brook/src/hash"
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/brook_main")
    execute_process(COMMAND /usr/bin/install_name_tool
      -delete_rpath "/Users/alex/brook/src/agent"
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/brook_main")
    execute_process(COMMAND /usr/bin/install_name_tool
      -delete_rpath "/Users/alex/brook/src/server"
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/brook_main")
    execute_process(COMMAND /usr/bin/install_name_tool
      -delete_rpath "/Users/alex/brook/src/sorted_buffer"
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/brook_main")
    execute_process(COMMAND /usr/bin/install_name_tool
      -delete_rpath "/Users/alex/brook/src/message"
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/brook_main")
    execute_process(COMMAND /usr/bin/install_name_tool
      -delete_rpath "/Users/alex/brook/src/core"
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/brook_main")
    execute_process(COMMAND /usr/bin/install_name_tool
      -delete_rpath "/Users/alex/brook/src/in_memory_store"
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/brook_main")
    if(CMAKE_INSTALL_DO_STRIP)
      execute_process(COMMAND "/usr/bin/strip" "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/brook_main")
    endif()
  endif()
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/bin" TYPE FILE FILES "/Users/alex/brook/src/core/run.sh")
endif()

