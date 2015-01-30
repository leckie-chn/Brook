# Build test executable
set(LIBS mrml mpich mpichcxx base strutil sorted_buffer in_memory_store hash protobuf gflags gtest boost_filesystem boost_system)
add_executable(mrml_main mrml_main.cc)
target_link_libraries(mrml_main ${LIBS})

# Install
install(TARGETS mrml_main DESTINATION bin/test)
FILE(GLOB FILES "${CMAKE_CURRENT_SOURCE_DIR}/*.sh")
install(FILES ${FILES} DESTINATION bin/test)

