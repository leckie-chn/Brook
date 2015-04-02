# Build library communication
add_library(communication mpi_sendrecv.cc signaling_queue.cc)

# Build unittests
set(LIBS communication util mpich mpicxx message gtest protobuf)

add_executable(mpi_sendrecv_test mpi_sendrecv_test.cc)
target_link_libraries(mpi_sendrecv_test ${LIBS})

# Install library and head files
# install(TARGETS communication DESTINATION bin/communication)
FILE(GLOB HEADER_FILES "${CMAKE_CURRENT_SOURCE_DIR}/*.h")
install(FILES ${HEADER_FILES} DESTINATION include/communication)
