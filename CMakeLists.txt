cmake_minimum_required(VERSION 3.10)
project(regex-fa)

set(APP_DIR "${CMAKE_CURRENT_SOURCE_DIR}/app")
set(SRC_DIR "${CMAKE_CURRENT_SOURCE_DIR}/source")
set(TEST_DIR "${CMAKE_CURRENT_SOURCE_DIR}/tests")
set(LIB_DIR "${CMAKE_CURRENT_SOURCE_DIR}/libraries")


# Source files
set(SOURCES
        "${SRC_DIR}/RegexNFA.cpp"
        "${SRC_DIR}/NFABuilder.cpp")

# Test files
set(TEST_SOURCES
        "${TEST_DIR}/main.cpp"
        "${TEST_DIR}/RegexNFATest.cpp")


# Executable definition and properties
add_executable(${PROJECT_NAME} ${APP_DIR}/main.cpp)
set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 14)


# Regex-FA
set(REGEX_FA_LIB regex-fa-lib)
add_library(${REGEX_FA_LIB} ${SOURCES})
set_property(TARGET ${REGEX_FA_LIB} PROPERTY CXX_STANDARD 14)
target_link_libraries(${PROJECT_NAME} ${REGEX_FA_LIB})


# CMD-Parser
set(CMD_PARSER_DIR "${LIB_DIR}/cmd-parser")
add_subdirectory("${CMD_PARSER_DIR}")
target_link_libraries(${PROJECT_NAME} "cmd-parser")
target_include_directories(${PROJECT_NAME} PRIVATE "${CMD_PARSER_DIR}/include")


# Unit Tests
option(BUILD_TESTS "Determines whether to build tests." OFF)
if(BUILD_TESTS)
    enable_testing()

    set(REGEX_FA_TESTS regex-fa-tests)
    add_executable(${REGEX_FA_TESTS} ${TEST_SOURCES})
    target_link_libraries(${REGEX_FA_TESTS} PUBLIC ${REGEX_FA_LIB})
    set_property(TARGET ${REGEX_FA_TESTS} PROPERTY CXX_STANDARD 14)

    # catch2
    set(CATCH_DIR "${LIB_DIR}/catch2")
    target_include_directories(${REGEX_FA_TESTS} PRIVATE "${CATCH_DIR}")

    add_test(NAME regex-fa-test COMMAND ${REGEX_FA_TESTS})
endif()