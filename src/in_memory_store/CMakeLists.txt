# Build library kv_store

# Build unittests.
set(LIBS base gtest)

add_executable(sparse_vector_test sparse_vector_test.cc)
target_link_libraries(sparse_vector_test gtest_main ${LIBS})

add_executable(dense_vector_test dense_vector_test.cc)
target_link_libraries(dense_vector_test gtest_main ${LIBS})

add_executable(sparse_table_test sparse_table_test.cc)
target_link_libraries(sparse_table_test gtest_main ${LIBS})

# Install library and header files.
