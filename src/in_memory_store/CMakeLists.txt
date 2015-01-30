# Build library in_memory_store.
add_library(in_memory_store sparse_vector.cc dense_vector.cc)

# Build unittests
set(LIBS in_memory_store base gtest)

add_executable(sparse_vector_test sparse_vector_test.cc)
target_link_libraries(sparse_vector_test gtest_main ${LIBS})

# Install library and header files
install(TARGETS in_memory_store DESTINATION bin/in_memory_store)
FILE(GLOB HEADER_FILES "${CMAKE_CURRENT_SOURCE_DIR}/*.h")
install(FILES ${HEADER_FILES} DESTINATION include/in_memory_store)
