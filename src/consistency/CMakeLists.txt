# Build Library consistency.
add_library(consistency consistency.cc fifo.cc)

# Build unittests.
set(LIBS consistency gtest util)

add_executable(fifo_test fifo_test.cc)
target_link_libraries(fifo_test gtest_main ${LIBS})

add_executable(consistency_test consistency_test.cc)
target_link_libraries(consistency_test gtest_main ${LIBS})

# Install library and head files.
