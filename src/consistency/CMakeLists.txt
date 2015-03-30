# Build Library consistency.
add_library(consistency consistency.cc)

# Build unittests.
set(LIBS gtest util)
add_executable(fifo_test fifo_test.cc)
target_link_libraries(fifo_test gtest_main ${LIBS})

# Install library and head files.
