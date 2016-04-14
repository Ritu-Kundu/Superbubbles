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
add_subdirectory(tests)

#// Source files
set(SOURCE_FILES
        src/Superbubble/algorithms/linear/CandidateList.cpp
        src/Superbubble/algorithms/linear/CandidateList.hpp
        src/Superbubble/algorithms/linear/DAG.cpp
        src/Superbubble/algorithms/linear/DAG.hpp
        src/Superbubble/algorithms/linear/DetectSuperBubble.cpp
        src/Superbubble/algorithms/linear/DetectSuperBubble.hpp
        src/Superbubble/algorithms/linear/globalDefs.hpp
        src/Superbubble/algorithms/linear/Graph.cpp
        src/Superbubble/algorithms/linear/Graph.hpp
        src/Superbubble/algorithms/linear/helper.cpp
        src/Superbubble/algorithms/linear/helperDefs.hpp
        src/Superbubble/algorithms/linear/Subgraph.cpp
        src/Superbubble/algorithms/linear/Subgraph.hpp
        src/Superbubble/algorithms/linear/supbub.cpp)

add_executable(
        supbub
        ${SOURCE_FILES}
)

target_link_libraries(supbub sdsl divsufsort)