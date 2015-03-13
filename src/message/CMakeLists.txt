# Build protobuf
protobuf_generate_cpp(PROTO_SRCS PROTO_HDRS message.proto)

# Build library message
add_library(message ${PROTO_SRCS})

set(LIBS message base gtest protobuf)

# Build unittests
add_executable(message_test message_test.cc)
target_link_libraries(message_test gtest_main ${LIBS})

# Install library and header files
install(TARGETS message DESTINATION bin/message)
FILE(GLOB HEADER_FILES "${CMAKE_CURRENT_SOURCE_DIR}/*.h")
install(FILES ${HEADER_FILES} DESTINATION include/message)
