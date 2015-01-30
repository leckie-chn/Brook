# Build unittests
set(LIBS base gtest)

add_executable(sparse_vector_test sparse_vector_test.cc)
target_link_libraries(sparse_vector_test gtest_main ${LIBS})

add_executable(dense_vector_test dense_vector_test.cc)
target_link_libraries(dense_vector_test gtest_main ${LIBS})

# Install library and header files
FILE(GLOB HEADER_FILES "${CMAKE_CURRENT_SOURCE_DIR}/*.h")
install(FILES ${HEADER_FILES} DESTINATION include/in_memory_store)
