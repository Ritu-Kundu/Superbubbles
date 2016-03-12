cmake_minimum_required(VERSION 3.4)
project(Superbubbles)

#// Project flags
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -pthread")
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
find_package(Boost REQUIRED)
include_directories(${BOOST_INCLUDE_DIRS})

###########
# sources #
###########
set(SOURCE_FILES
        src/CandidateList.cpp
        src/CandidateList.hpp
        src/DAG.cpp
        src/DAG.hpp
        src/DetectSuperBubble.cpp
        src/DetectSuperBubble.hpp
        src/Graph.cpp
        src/Graph.hpp
        src/helper.cpp
        src/helperDefs.hpp
        src/Subgraph.cpp
        src/Subgraph.hpp
        src/supbub.cpp)

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