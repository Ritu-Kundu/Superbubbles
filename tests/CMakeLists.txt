cmake_minimum_required(VERSION 3.5)
project(unit_tests)

#// Project flags
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS " ${CMAKE_CXX_FLAGS} -std=c++14 -pthread")
#// Setting the build output to ./build
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/../build/")

#// GTest framework for unit testing
enable_testing()
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})


set(TEST_FILES
        test.cpp)

add_executable(
        UnitTests
        ${TEST_FILES})

target_link_libraries(UnitTests gtest)
add_test(UnitTests ${TEST_FILES})