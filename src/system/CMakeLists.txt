# Build library system

# Build unittests
set(LIBS util gtest pthread)

add_executable(mutex_test mutex_test.cc)
target_link_libraries(mutex_test gtest_main ${LIBS})

# Install library and header files
