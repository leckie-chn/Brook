# Build library agent
add_library(agent agent.cc)

set(LIBS agent base gflags)

# Build main program
add_executable(agent_main agent_main.cc)
target_link_libraries(agent_main ${LIBS})

# Install library and head files
install(TARGETS agent DESTINATION bin/agent)
install(TARGETS agent_main DESTINATION bin/agent)
FILE(GLOB HEADER_FILES "${CMAKE_CURRENT_SOURCE_DIR}/*.h")
install(FILES ${HEADER_FILES} DESTINATION include/agent)
