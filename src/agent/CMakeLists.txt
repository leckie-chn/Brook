# Build library agent
add_library(agent agent.cc)

set(LIBS agent gtest base strutil message protobuf)

# Install library and header files
install(TARGETS agent DESTINATION bin/agent)
FILE(GLOB HEADER_FILES "${CMAKE_CURRENT_SOURCE_DIR}/*.h")
install(FILES ${HEADER_FILES} DESTINATION include/agent)
