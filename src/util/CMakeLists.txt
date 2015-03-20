# Build library util
add_library(util logging.cc strcodec.cc split_string.cc stringprintf.cc)

# Build unittests.
set(LIBS util gtest)

add_executable(class_register_test class_register_test.cc class_register_test_helper.cc)
target_link_libraries(class_register_test gtest_main ${LIBS})

add_executable(stl-util_test stl-util_test.cc)
target_link_libraries(stl-util_test gtest_main ${LIBS})

add_executable(strcodec_test strcodec_test.cc)
target_link_libraries(strcodec_test base gtest_main ${LIBS})

add_executable(split_string_test split_string_test.cc)
target_link_libraries(split_string_test gtest_main ${LIBS})

add_executable(stringprintf_test stringprintf_test.cc)
target_link_libraries(stringprintf_test gtest_main ${LIBS})

add_executable(join_strings_test join_strings_test.cc)
target_link_libraries(join_strings_test gtest_main ${LIBS})

# Install library and header files
install(TARGETS util DESTINATION bin/util)
FILE(GLOB HEADER_FILES "${CMAKE_CURRENT_SOURCE_DUR}/*.h")
install(FILES ${HEADER_FILES} DESTINATION include/util)
