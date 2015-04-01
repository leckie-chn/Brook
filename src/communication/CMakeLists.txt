# Build library communication
add_library(communication mpi_communicator.cc)

# Build unittests

# Install library and head files
install(TARGETS communication DESTINATION bin/communication)
FILE(GLOB HEADER_FILES "${CMAKE_CURRENT_SOURCE_DIR}/*.h")
install(FILES ${HEADER_FILES} DESTINATION include/communication)
