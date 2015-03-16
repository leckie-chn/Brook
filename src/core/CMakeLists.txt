# Build executable
add_executable(brook_main brook_main.cc flags.cc)
target_link_libraries(brook_main mpich mpicxx agent server base gflags strutil)

# Install executable
install(TARGETS brook_main DESTINATION bin/)
FILE(GLOB SHELL_FILES "${CMAKE_CURRENT_SOURCE_DIR}/*.sh")
install(FILES ${SHELL_FILES} DESTINATION bin/)

# Add sub directory
add_subdirectory(ramdisk)
