# Build library server
add_library(server server.cc)

# Install library and header files
install(TARGETS server DESTINATION bin/server)
FILE(GLOB HEADER_FILES "${CMAKE_CURRENT_SOURCE_DIR}/.*h")
install(FILES ${HEADER_FILES} DESTINATION include/server)
