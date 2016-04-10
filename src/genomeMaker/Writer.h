//
// Created by alwyn on 4/10/16.
//

#ifndef SUPERBUBBLES_WRITER_H
#define SUPERBUBBLES_WRITER_H

#include <iostream>
#include <fstream>
#include <memory>
#include "../../include/eadib_log/Logger.h"

namespace genomeMaker {
    class Writer {
      public:
        Writer( const std::string &file_name );
        ~Writer();
        template<typename T> void write( const T &value );

      private:
        std::unique_ptr<std::ofstream> _output_stream;
    };

    /**
     * Constructor
     * @param file_name Name of the output file
     */
    Writer::Writer( const std::string &file_name ) :
        _output_stream( new std::ofstream )
    {
        _output_stream->open( (file_name + ".genome" ).c_str(), std::ios::out | std::ios::ate | std::ios::app );
        if( !_output_stream->is_open() ) {
            LOG_FATAL( "[genomeMaker::Writer::Writer( ", file_name, " )] Unable to open stream to file." );
        }

    }

    /**
     * Destructor
     */
    Writer::~Writer() {
        if( _output_stream ) {
            _output_stream->close();
        }
    }

    /**
     * Writes to the output stream (file)
     * @param value Value to write
     */
    template<typename T> void Writer::write( const T &value ) {
        (*_output_stream ) << value;
    }
}

#endif //SUPERBUBBLES_WRITER_H
