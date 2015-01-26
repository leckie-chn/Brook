# Build library base.
add_library(base logging.cc varint32.cc filepattern.cc)

# Build unittests
set(LIBS base protobuf gtest strutil)

# Install library and head files
install(TARGETS base DESTINATION bin/base)
FILE(GLOB HEADER_FILES "${CMAKE_CURRENT_SOURCE_DIR}/*.h")
install(FILES ${HEADER_FILES} DESTINATION include/base)
