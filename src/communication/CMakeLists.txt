# Build library communication
add_library(communication mpi_sendrecv.cc signaling_queue.cc)

# Build unittests
set(LIBS communication system util mpich mpicxx message gtest protobuf)

add_executable(mpi_sendrecv_test mpi_sendrecv_test.cc)
target_link_libraries(mpi_sendrecv_test ${LIBS})

add_executable(signaling_queue_test signaling_queue_test.cc)
target_link_libraries(signaling_queue_test gtest_main ${LIBS})

# Install library and head files
# install(TARGETS communication DESTINATION bin/communication)
FILE(GLOB HEADER_FILES "${CMAKE_CURRENT_SOURCE_DIR}/*.h")
install(FILES ${HEADER_FILES} DESTINATION include/communication)
