# Build library parameter


# Build unittests
add_executable(dense_vector_tmpl_test dense_vector_tmpl_test.cc)
target_link_libraries(dense_vector_tmpl_test gtest_main)

add_executable(sparse_vector_tmpl_test sparse_vector_tmpl_test.cc)
target_link_libraries(sparse_vector_tmpl_test gtest_main)
