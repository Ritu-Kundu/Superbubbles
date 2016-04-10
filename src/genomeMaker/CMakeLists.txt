cmake_minimum_required(VERSION 3.2)
project(genome_maker)

#// Project flags
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS " ${CMAKE_CXX_FLAGS} -std=c++14 -pthread")
#// Setting the build output to ./build
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/../../build")


set(GENOME_MAKER
        gmaker.cpp
        Reader.cpp
        Reader.h
        Creator.cpp
        Creator.h
        tools/Randomiser.cpp
        tools/Randomiser.h
        tools/ProgressDisplay.cpp
        tools/ProgressDisplay.h
        Writer.h
        tools/CLParser.cpp
        tools/CLParser.h)

add_executable(
        GenomeMaker
        ${GENOME_MAKER}
)