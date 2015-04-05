# Build library system
add_library(system filepattern.cc condition_variable.cc)

# Build unittests
set(LIBS system util gtest pthread)

add_executable(mutex_test mutex_test.cc)
target_link_libraries(mutex_test gtest_main ${LIBS})

add_executable(filepattern_test filepattern_test.cc)
target_link_libraries(filepattern_test gtest_main ${LIBS})

add_executable(condition_variable_test condition_variable_test.cc)
target_link_libraries(condition_variable_test gtest_main ${LIBS})

# Install library and header files
install(TARGETS system DESTINATION bin/system)
FILE(GLOB HEADER_FILES "${CMAKE_CURRENT_SOURCE_DIR}/*.h")
install(FILES ${HEADER_FILES} DESTINATION include/system)
