# Build library parameter
add_library(parameter bitmap.cc)

# Build unittests
set(LIBS parameter util gtest snappy)

add_executable(dense_vector_tmpl_test dense_vector_tmpl_test.cc)
target_link_libraries(dense_vector_tmpl_test gtest_main ${LIBS})

add_executable(sparse_vector_tmpl_test sparse_vector_tmpl_test.cc)
target_link_libraries(sparse_vector_tmpl_test gtest_main ${LIBS})

add_executable(dense_matrix_tmpl_test dense_matrix_tmpl_test.cc)
target_link_libraries(dense_matrix_tmpl_test gtest_main ${LIBS})

add_executable(sparse_matrix_tmpl_test sparse_matrix_tmpl_test.cc)
target_link_libraries(sparse_matrix_tmpl_test gtest_main ${LIBS})

add_executable(carray_vector_tmpl_test carray_vector_tmpl_test.cc)
target_link_libraries(carray_vector_tmpl_test gtest_main ${LIBS})

add_executable(bitmap_test bitmap_test.cc)
target_link_libraries(bitmap_test gtest_main ${LIBS})
