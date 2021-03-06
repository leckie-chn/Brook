# Build library util
add_library(util md5_hash.cc simple_hash.cc logging.cc strcodec.cc split_string.cc stringprintf.cc bitmap.cc)

# Build unittests.
set(LIBS util gtest snappy)

add_executable(class_register_test class_register_test.cc class_register_test_helper.cc)
target_link_libraries(class_register_test gtest_main ${LIBS})

add_executable(stl-util_test stl-util_test.cc)
target_link_libraries(stl-util_test gtest_main ${LIBS})

add_executable(strcodec_test strcodec_test.cc)
target_link_libraries(strcodec_test gtest_main ${LIBS})

add_executable(split_string_test split_string_test.cc)
target_link_libraries(split_string_test gtest_main ${LIBS})

add_executable(stringprintf_test stringprintf_test.cc)
target_link_libraries(stringprintf_test gtest_main ${LIBS})

add_executable(join_strings_test join_strings_test.cc)
target_link_libraries(join_strings_test gtest_main ${LIBS})

add_executable(file_util_test file_util_test.cc)
target_link_libraries(file_util_test gtest_main ${LIBS})

add_executable(md5_hash_test md5_hash_test.cc)
target_link_libraries(md5_hash_test gtest_main ${LIBS})

add_executable(bitmap_test bitmap_test.cc)
target_link_libraries(bitmap_test gtest_main ${LIBS})

# Install library and header files
install(TARGETS util DESTINATION bin/util)
FILE(GLOB HEADER_FILES "${CMAKE_CURRENT_SOURCE_DUR}/*.h")
install(FILES ${HEADER_FILES} DESTINATION include/util)
