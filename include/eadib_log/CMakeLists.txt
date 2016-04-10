cmake_minimum_required(VERSION 3.2)
project(genome_maker)

#// Project flags
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS " ${CMAKE_CXX_FLAGS} -std=c++14 -pthread")
#// Setting the build output to ./build
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/../../build")

set(EADLIB_LOGGER
        Logger.h
        log_configuration/OutputConfiguration.h
        log_formatters/Formatter_Terminal.h
        log_formatters/Formatter.h
        log_configuration/TimeStamp.h
        log_configuration/LogConfig.h
        log_outputs/LogOutput.h
        log_configuration/LogLevel_types.h
        log_outputs/LogOutput_FileAppend.h
        log_outputs/LogOutput_FileOverwrite.h
        log_outputs/LogOutput_FileNew.h
        log_formatters/Formatter_types.h
        log_outputs/LogOutput_types.h
        log_outputs/LogOutput_Terminal.h
        )

add_library(
        ead_logger
        STATIC
        ${EADLIB_LOGGER})

SET_TARGET_PROPERTIES(ead_logger PROPERTIES LINKER_LANGUAGE CXX)