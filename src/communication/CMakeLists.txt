# Build library communication

# Build unittests
set(LIBS util mpich mpicxx message gtest protobuf)

add_executable(mpi_communicator_test mpi_communicator_test.cc)
target_link_libraries(mpi_communicator_test ${LIBS})

# Install library and head files
# install(TARGETS communication DESTINATION bin/communication)
FILE(GLOB HEADER_FILES "${CMAKE_CURRENT_SOURCE_DIR}/*.h")
install(FILES ${HEADER_FILES} DESTINATION include/communication)
