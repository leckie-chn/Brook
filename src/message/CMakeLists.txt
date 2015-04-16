# Build protobuf
protobuf_generate_cpp(PROTO_SRCS PROTO_HDRS message.proto)

# Build library message
add_library(message ${PROTO_SRCS} reader.cc ../util/split_string.cc)

set(LIBS message protobuf gtest util)

# Build unittests.
add_executable(message_test message_test.cc)
target_link_libraries(message_test gtest_main ${LIBS})

add_executable(reader_test reader_test.cc)
target_link_libraries(reader_test gtest_main ${LIBS})

add_executable(partition_test partition_test.cc)
target_link_libraries(partition_test gtest_main ${LIBS})

# Install library and header files
install(TARGETS message DESTINATION bin/message)
FILE(GLOB HEADER_FILES "${CMAKE_CURRENT_SOURCE_DIR}/*.h")
install(FILES ${HEADER_FILES} DESTINATION include/message)
