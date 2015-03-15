# Build library agent
add_library(agent agent.cc reader.cc)

set(LIBS agent gtest base strutil message protobuf)

# Build unittests
add_executable(reader_test reader_test.cc)
target_link_libraries(reader_test gtest_main ${LIBS})

# Install library and header files
install(TARGETS agent DESTINATION bin/agent)
FILE(GLOB HEADER_FILES "${CMAKE_CURRENT_SOURCE_DIR}/*.h")
install(FILES ${HEADER_FILES} DESTINATION include/agent)
