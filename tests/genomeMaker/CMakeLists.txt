cmake_minimum_required(VERSION 3.2)
project(genome_maker_tests)

#// Project flags
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS " ${CMAKE_CXX_FLAGS} -std=c++14 -pthread")
#// Setting the build output to ./build
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/../builds/")

#// GTest framework for unit testing
enable_testing()
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

set(TEST_FILES
        Creator_tests.cpp
        main.cpp)

add_executable(
        genomeMaker_Tests
        ${TEST_FILES}
)

target_link_libraries(genomeMaker_Tests gtest)
add_test(genomeMaker_Tests ${TEST_FILES})