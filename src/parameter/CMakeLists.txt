# Build library parameter

# Build unittests
set(LIBS util gtest)

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

add_executable(update_tmpl_test update_tmpl_test.cc)
target_link_libraries(update_tmpl_test gtest_main ${LIBS})

add_executable(random_queue_tmpl_test random_queue_tmpl_test.cc)
target_link_libraries(random_queue_tmpl_test gtest_main ${LIBS})

add_executable(version_buffer_tmpl_test version_buffer_tmpl_test.cc)
target_link_libraries(version_buffer_tmpl_test gtest_main ${LIBS})

add_executable(parameter_tmpl_test parameter_tmpl_test.cc)
target_link_libraries(parameter_tmpl_test gtest_main ${LIBS})

add_executable(skip_list_tmpl_test skip_list_tmpl_test.cc)
target_link_libraries(skip_list_tmpl_test gtest_main ${LIBS})
