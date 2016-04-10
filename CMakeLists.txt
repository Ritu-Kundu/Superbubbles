cmake_minimum_required(VERSION 3.2)
project(Superbubbles)

#// Project flags
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_C_FLAG "$CMAKE_C_FLAGE} -D_USE_64")
set(CMAKE_CXX_FLAGS " ${CMAKE_CXX_FLAGS} -std=c++14 -pthread")
#// Setting the build output to ./build
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/build")

#// SDSL library
include_directories(include)
include_directories(include/sdsl)
find_library(sdsl lib)
find_library(divsufsort lib)
link_directories(lib)

#// Add all the sub-project directories
add_subdirectory(src/genomeMaker)
add_subdirectory(tests/genomeMaker)
add_subdirectory(include/eadib_log)

#// Source files
set(SOURCE_FILES
        src/algo_linear/CandidateList.cpp
        src/algo_linear/CandidateList.hpp
        src/algo_linear/DAG.cpp
        src/algo_linear/DAG.hpp
        src/algo_linear/DetectSuperBubble.cpp
        src/algo_linear/DetectSuperBubble.hpp
        src/algo_linear/globalDefs.hpp
        src/algo_linear/Graph.cpp
        src/algo_linear/Graph.hpp
        src/algo_linear/helper.cpp
        src/algo_linear/helperDefs.hpp
        src/algo_linear/Subgraph.cpp
        src/algo_linear/Subgraph.hpp
        src/algo_linear/supbub.cpp)

add_executable(
        SuperBubbles
        ${SOURCE_FILES}
)

target_link_libraries(SuperBubbles sdsl divsufsort)