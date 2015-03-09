# Build library kv_store

# Build unittests.
set(LIBS base gtest)

add_executable(sparse_vector_test sparse_vector_test.cc)
target_link_libraries(sparse_vector_test gtest_main ${LIBS})

# Install library and header files.
