cmake_minimum_required(VERSION 3.4)
project(Superbubbles)

#// Project flags
set(CMAKE_C_FLAG "$CMAKE_C_FLAGE} -D_USE_64")
set(CMAKE_CXX_FLAGS " ${CMAKE_CXX_FLAGS} -std=c++11 -pthread")
#// Setting the build output to ./build
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/build")

#// GTest framework for unit testing
enable_testing()
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

#// SDSL library
include_directories(include)
include_directories(include/sdsl)
find_library(ead_logger lib)
find_library(sdsl lib)
find_library(divsufsort lib)
link_directories(lib)

#// Boost (for logging)
#find_package(Boost REQUIRED)
#include_directories(${BOOST_INCLUDE_DIRS})

###########
# sources #
###########
set(SOURCE_FILES
        src/algo_linear/CandidateList.cpp
        src/algo_linear/CandidateList.hpp
        src/algo_linear/DAG.cpp
        src/algo_linear/DAG.hpp
        src/algo_linear/DetectSuperBubble.cpp
        src/algo_linear/DetectSuperBubble.hpp
        src/algo_linear/Graph.cpp
        src/algo_linear/Graph.hpp
        src/algo_linear/helper.cpp
        src/algo_linear/helperDefs.hpp
        src/algo_linear/Subgraph.cpp
        src/algo_linear/Subgraph.hpp
        src/algo_linear/supbub.cpp)

set(TEST_FILES
tests/test_main.cpp)

######################
# Artifacts produced #
######################
add_executable(
SuperBubbles
${SOURCE_FILES}
)

add_executable(
UnitTests
${TEST_FILES}
)

###########
# Linking #
###########
target_link_libraries(UnitTests gtest)
add_test(UnitTests ${TEST_FILES})

target_link_libraries(SuperBubbles ead_logger sdsl divsufsort)