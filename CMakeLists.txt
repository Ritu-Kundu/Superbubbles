cmake_minimum_required(VERSION 3.2)
project(Superbubbles)

#// Project flags
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_C_FLAG "$CMAKE_C_FLAGE} -D_USE_64")
set(CMAKE_CXX_FLAGS " ${CMAKE_CXX_FLAGS} -std=c++14 -pthread")
#// Setting the build output to ./build
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/build")

#// GTest framework for unit testing
enable_testing()
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

#// SDSL library
include_directories(include)
include_directories(include/sdsl)
find_library(sdsl lib)
find_library(divsufsort lib)
link_directories(lib)

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
        src/algo_linear/globalDefs.hpp
        src/algo_linear/Graph.cpp
        src/algo_linear/Graph.hpp
        src/algo_linear/helper.cpp
        src/algo_linear/helperDefs.hpp
        src/algo_linear/Subgraph.cpp
        src/algo_linear/Subgraph.hpp
        src/algo_linear/supbub.cpp)

set( EADLIB_LOGGER
        include/eadib_log/Logger.h
        include/eadib_log/log_configuration/OutputConfiguration.h
        include/eadib_log/log_formatters/Formatter_Terminal.h
        include/eadib_log/log_formatters/Formatter.h
        include/eadib_log/log_configuration/TimeStamp.h
        include/eadib_log/log_configuration/LogConfig.h
        include/eadib_log/log_outputs/LogOutput.h
        include/eadib_log/log_configuration/LogLevel_types.h
        include/eadib_log/log_outputs/LogOutput_FileAppend.h
        include/eadib_log/log_outputs/LogOutput_FileOverwrite.h
        include/eadib_log/log_outputs/LogOutput_FileNew.h
        include/eadib_log/log_formatters/Formatter_types.h
        include/eadib_log/log_outputs/LogOutput_types.h
        include/eadib_log/log_outputs/LogOutput_Terminal.h
        )

set(GENOME_MAKER
        src/genomeMaker/gmaker.cpp src/genomeMaker/Reader.cpp src/genomeMaker/Reader.h src/genomeMaker/Creator.cpp src/genomeMaker/Creator.h)

set(TEST_FILES
        tests/test_main.cpp tests/genomeMaker/Creator_tests.cpp)

######################
# Artifacts produced #
######################
add_library(
        ead_logger
        STATIC
        ${EADLIB_LOGGER})

add_executable(
        SuperBubbles
        ${SOURCE_FILES}
)

add_executable(
        GenomeMaker
        ${GENOME_MAKER}
)

add_executable(
        UnitTests
        ${TEST_FILES}
)

###########
# Linking #
###########
SET_TARGET_PROPERTIES(ead_logger PROPERTIES LINKER_LANGUAGE CXX)

target_link_libraries(UnitTests gtest )
add_test(UnitTests ${TEST_FILES})

target_link_libraries(SuperBubbles sdsl divsufsort ead_logger)

target_link_libraries(GenomeMaker ead_logger)