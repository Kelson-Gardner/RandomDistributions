cmake_minimum_required(VERSION 3.14)

set(PROJECT_NAME RandDistributions)
set(UNIT_TEST_RUNNER UnitTestRunner)
project(${PROJECT_NAME})

set(HEADER_FILES distributions.hpp)
set(SOURCE_FILES distributions.cpp)
set(UNIT_TEST_FILES testDistributions.cpp)

add_executable(${PROJECT_NAME} ${SOURCE_FILES} ${HEADER_FILES} Assignment2.cpp)
add_executable(${UNIT_TEST_RUNNER} ${SOURCE_FILES} ${HEADER_FILES} ${UNIT_TEST_FILES})

set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 20)
set_property(TARGET ${UNIT_TEST_RUNNER} PROPERTY CXX_STANDARD 20)

find_program(CLANG_FORMAT "clang-format")
if (CLANG_FORMAT)
unset(SOURCE_FILES_PATHS)
foreach(SOURCE_FILE ${HEADER_FILES} ${SOURCE_FILES} ${UNIT_TEST_FILES})
get_source_file_property(WHERE ${SOURCE_FILE} LOCATION)
set(SOURCE_FILES_PATHS ${SOURCE_FILES_PATHS} ${WHERE})
endforeach()
add_custom_target(
ClangFormat
COMMAND ${CLANG_FORMAT}
-i
-style=file
${SOURCE_FILES_PATHS})
add_dependencies(${PROJECT_NAME} ClangFormat)
endif()

if (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
target_compile_options(RandDistributions PRIVATE /W4 /permissive-)
elseif (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
target_compile_options(RandDistributions PRIVATE -Wall -Wextra -pedantic)
elseif (CMAKE_CXX_COMPILER_ID MATCHES "Clang")
target_compile_options(RandDistributions PRIVATE -Wall -Wextra -pedantic)
endif()

include(FetchContent)
FetchContent_Declare(
    googletest
    GIT_REPOSITORY  https://github.com/google/googletest.git
    GIT_TAG         v1.15.0
)
set(gtest_forced_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

target_link_libraries(${UNIT_TEST_RUNNER} gtest_main)
