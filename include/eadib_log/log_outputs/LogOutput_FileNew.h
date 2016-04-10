//
// Created by alwyn on 4/8/16.
//

#ifndef EADLIB_LOGOUTPUT_FILENEW_H
#define EADLIB_LOGOUTPUT_FILENEW_H

#include <iostream>
#include <fstream>
#include <memory>
#include "LogOutput.h"

namespace eadlib {
    namespace log {
        class LogOutput_FileNew : public LogOutput {
          public:
            LogOutput_FileNew() : _output_stream( new std::ofstream ) { }
            ~LogOutput_FileNew();
            void open_ostream( const std::string &name );
            void close_ostream();
            void write( const std::string &msg );
          private:
            std::unique_ptr<std::ofstream> _output_stream;
        };

        //-----------------------------------------------------------------------------------------------------------------
        // LogOutput_FileAppend class method implementations
        //-----------------------------------------------------------------------------------------------------------------
        /**
         * Destructor
         */
        inline LogOutput_FileNew::~LogOutput_FileNew() {
            if( _output_stream ) {
                close_ostream();
            }
        }

        /**
         * Opens output stream
         * @param file_name Name of the file
         */
        inline void LogOutput_FileNew::open_ostream( const std::string &file_name ) {
            std::string formatted_name = file_name + "_" + TimeStamp().getTimeStamp( "%Y%m%d-%H%M%S" ) + ".txt";
            _output_stream->open( formatted_name.c_str(), std::ios::out | std::ios::ate | std::ios::app ); //std::ios_base::binary | std::ios_base::out
            if( !_output_stream->is_open() ) {
                throw( std::runtime_error( "eadlib::Logger: Unable to open output stream" ) );
            }
        }

        /**
         * Closes output stream
         */
        inline void LogOutput_FileNew::close_ostream() {
            if( _output_stream ) {
                _output_stream->close();
            }
        }

        /**
         * Writes to the output stream
         * @param msg Message to write
         */
        inline void LogOutput_FileNew::write( const std::string &msg ) {
            (*_output_stream ) << msg << std::endl;
        }
    }
}

#endif //EADLIB_LOGOUTPUT_FILENEW_H
