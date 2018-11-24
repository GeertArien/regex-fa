cmake_minimum_required(VERSION 3.12)
project(RegexFA)

set(SRC_DIR "${CMAKE_CURRENT_SOURCE_DIR}/source")
set(LIB_DIR "${CMAKE_CURRENT_SOURCE_DIR}/libraries")

# Source files
set(SOURCES
        "${SRC_DIR}/main.cpp"
        "${SRC_DIR}/regex/RegexNFA.cpp"
        "${SRC_DIR}/regex/NFABuilder.cpp")

# Executable definition and properties
add_executable(${PROJECT_NAME} ${SOURCES})
set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 14)

# CMD-Parser
set(CMD_PARSER_DIR "${LIB_DIR}/cmd-parser")
add_subdirectory("${CMD_PARSER_DIR}")
target_link_libraries(${PROJECT_NAME} "cmd-parser")
target_include_directories(${PROJECT_NAME} PRIVATE "${CMD_PARSER_DIR}/include")
