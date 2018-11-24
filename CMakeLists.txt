cmake_minimum_required(VERSION 3.12)
project(RegexFA)

set(CMAKE_CXX_STANDARD 14)

# Source files
set(SRC_DIR "${CMAKE_CURRENT_SOURCE_DIR}/source")
set(SOURCES
        "${SRC_DIR}/main.cpp"
        "${SRC_DIR}/cmd_line/CMDParser.h"
        "${SRC_DIR}/cmd_line/CMDParser.cpp"
        "${SRC_DIR}/cmd_line/CMDArgument.h"
        "${SRC_DIR}/cmd_line/CMDArgument.cpp" source/regex/State.cpp source/regex/State.h source/regex/RegexNFA.cpp source/regex/RegexNFA.h source/regex/NFABuilder.cpp source/regex/NFABuilder.h)

# Executable definition and properties
add_executable(${PROJECT_NAME} ${SOURCES})
set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 14)
