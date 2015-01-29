# Build protobuf
protobuf_generate_cpp(PROTO_SRCS PROTO_HDRS protofile.proto)

# Build library 
add_library(mrml ${PROTO_SRCS} mapreduce.cc protofile.cc reader.cc flags.cc)

set(LIBS mrml base strutil hash sorted_buffer protobuf gflags gtest boost_filesystem boost_system mpich mpichcxx)

# Build unittests
add_executable(protofile_test protofile_test.cc)
target_link_libraries(protofile_test gtest_main ${LIBS})

add_executable(reader_test reader_test.cc)
target_link_libraries(reader_test gtest_main ${LIBS})

add_executable(utils_test utils_test.cc)
target_link_libraries(utils_test gtest_main ${LIBS})

add_executable(register_test register_test.cc)
target_link_libraries(register_test gtest_main ${LIBS})

# Install library and header files
install(TARGETS mrml DESTINATION bin/mrml)
FILE(GLOB HEADER_FILES "${CMAKE_CURRENT_SOURCE_DIR}/*.h")
install(FILES ${HEADER_FILES} DESTINATION include/mrml)

add_subdirectory(test)
