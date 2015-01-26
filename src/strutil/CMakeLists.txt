# Build library strutil.
add_library(strutil split_string.cc stringprintf.cc)

# Build unittests.
set(LIBS strutil base gtest)

add_executable(split_string_test split_string_test.cc)
target_link_libraries(split_string_test gtest_main ${LIBS})

add_executable(stringprintf_test stringprintf_test.cc)
target_link_libraries(stringprintf_test gtest_main ${LIBS})

add_executable(join_strings_test join_strings_test.cc)
target_link_libraries(join_strings_test gtest_main ${LIBS})

# Install library and head files
install(TARGETS strutil DESTINATION bin/strutil)
FILE(GLOB HEADER_FILES "${CMAKE_CURRENT_SOURCE_DIR}/*.h")
install(FILES ${HEADER_FILES} DESTINATION include/strutil)
