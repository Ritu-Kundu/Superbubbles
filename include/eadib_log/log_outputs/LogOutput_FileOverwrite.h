//
// Created by alwyn on 3/15/16.
//

#ifndef EADLIB_LOGOUTPUT_FILEOVERWRITE_H
#define EADLIB_LOGOUTPUT_FILEOVERWRITE_H

#include <iostream>
#include <fstream>
#include <memory>
#include "LogOutput.h"

namespace eadlib {
    namespace log {
        class LogOutput_FileOverwrite : public LogOutput {
          public:
            LogOutput_FileOverwrite() : _output_stream( new std::ofstream ) { }
            ~LogOutput_FileOverwrite();
            void open_ostream( const std::string &name );
            void close_ostream();
            void write( const std::string &msg );
          private:
            std::unique_ptr<std::ofstream> _output_stream;
        };

        //-----------------------------------------------------------------------------------------------------------------
        // LogOutput_FileOverwrite class method implementations
        //-----------------------------------------------------------------------------------------------------------------
        /**
         * Destructor
         */
        inline eadlib::log::LogOutput_FileOverwrite::~LogOutput_FileOverwrite() {
            if( _output_stream ) {
                close_ostream();
            }
        }

        /**
         * Opens output stream
         * @param file_name Name of the file
         */
        inline void eadlib::log::LogOutput_FileOverwrite::open_ostream( const std::string &file_name ) {
            std::string formatted_name = file_name + ".txt";
            _output_stream->open( formatted_name.c_str(), std::ofstream::out | std::ofstream::trunc ); //std::ios_base::binary | std::ios_base::out
            if( !_output_stream->is_open() ) {
                throw( std::runtime_error( "eadlib::Logger: Unable to open output stream" ) );
            }
        }

        /**
         * Closes output stream
         */
        inline void eadlib::log::LogOutput_FileOverwrite::close_ostream() {
            if( _output_stream ) {
                close_ostream();
            }
        }

        /**
         * Writes to the output stream
         * @param msg Message to write
         */
        inline void eadlib::log::LogOutput_FileOverwrite::write( const std::string &msg ) {
            (*_output_stream ) << msg << std::endl;
        }
    }
}

#endif //EADLIB_LOGOUTPUT_FILEOVERWRITE_H
