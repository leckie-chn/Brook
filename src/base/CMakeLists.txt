# Build library base.
add_library(base logging.cc varint32.cc)

# Build unittests
set(LIBS base protobuf gtest strutil)

add_executable(class_register_test class_register_test.cc class_register_test_helper.cc)
target_link_libraries(class_register_test gtest_main ${LIBS})

add_executable(logging_test logging_test.cc)
target_link_libraries(logging_test gtest_main ${LIBS})

add_executable(stl-util_test stl-util_test.cc)
target_link_libraries(stl-util_test gtest_main ${LIBS})

add_executable(varint32_test varint32_test.cc)
target_link_libraries(varint32_test gtest_main ${LIBS})

add_executable(file_util_test file_util_test.cc)
target_link_libraries(file_util_test gtest_main ${LIBS})

# Install library and head files
install(TARGETS base DESTINATION bin/base)
FILE(GLOB HEADER_FILES "${CMAKE_CURRENT_SOURCE_DIR}/*.h")
install(FILES ${HEADER_FILES} DESTINATION include/base)
