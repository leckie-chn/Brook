# Build executable
set(LIBS util message gflags boost_filesystem boost_system mpich mpicxx)

add_executable(brook_main brook_main.cc brook.cc agent.cc server.cc flags.cc master.cc)
target_link_libraries(brook_main ${LIBS})

# Install executable and header files
install(TARGETS brook_main DESTINATION bin/executor)
FILE(GLOB HEADER_FILES "${CMAKE_CURRENT_SOURCE_DIR}/*.h")
install(FILES ${HEADER_FILES} DESTINATION include/executor)

