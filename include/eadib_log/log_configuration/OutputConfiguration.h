//
// Created by alwyn on 3/15/16.
//

#ifndef EADLIB_OUTPUT_CONFIGURATION_H
#define EADLIB_OUTPUT_CONFIGURATION_H

#include <memory>

#include "../log_outputs/LogOutput.h"
#include "../log_outputs/LogOutput_types.h"
#include "../log_formatters/Formatter.h"
#include "../log_formatters/Formatter_types.h"
#include "../log_outputs/LogOutput_Terminal.h"
#include "../log_outputs/LogOutput_FileAppend.h"
#include "../log_outputs/LogOutput_FileOverwrite.h"
#include "../log_formatters/Formatter_Terminal.h"
#include "../log_outputs/LogOutput_FileNew.h"

namespace eadlib {
    namespace log {
        class OutputConfiguration {
          public:
            OutputConfiguration( const std::string &name, const LogLevel_types::Type &log_level, const LogOutput_types::Type &output,
                                 const Formatter_types::Type &formatter );
            ~OutputConfiguration() {};
            OutputConfiguration( const OutputConfiguration & ) = delete;
            OutputConfiguration & operator=( const OutputConfiguration & ) = delete;
            OutputConfiguration( OutputConfiguration &&out_config );
            //Methods
            void setOutputLevel( LogLevel_types::Type level );
            void setOutputLevel( unsigned int level );
            unsigned int getOutputLevelCode();
            std::string getName();
            void send( const TimeStamp &ts, const uint32_t &msgNum, const LogLevel_types::Type &level, const std::string &msg );
          private:
            std::string _name;
            LogLevel_types::Type _output_level;
            std::unique_ptr<Formatter> _formatter;
            std::unique_ptr<LogOutput> _output;
        };

        //-----------------------------------------------------------------------------------------------------------------
        // Public "OutputConfiguration" class method implementations
        //-----------------------------------------------------------------------------------------------------------------
        /**
         * Constructor
         * @param formatType Formatter
         * @param outputType Output
         */
        inline OutputConfiguration::OutputConfiguration( const std::string &name, const LogLevel_types::Type &log_level, const LogOutput_types::Type &output,
                                                  const Formatter_types::Type &formatter ) :
            _name( name ),
            _output_level( log_level )
        {
            switch( output ){
                case LogOutput_types::Type::TERMINAL:
                    _output = std::unique_ptr<LogOutput_Terminal>( new LogOutput_Terminal );
                    break;
                case LogOutput_types::Type::FILE_APPEND:
                    _output = std::unique_ptr<LogOutput_FileAppend>( new LogOutput_FileAppend );
                    break;
                case LogOutput_types::Type::FILE_OVERWRITE:
                    _output = std::unique_ptr<LogOutput_FileOverwrite>( new LogOutput_FileOverwrite );
                    break;
                case LogOutput_types::Type::FILE_NEW:
                    _output = std::unique_ptr<LogOutput_FileNew>( new LogOutput_FileNew );
                    break;
            }
            switch( formatter ) {
                case Formatter_types::Type::TERMINAL:
                    _formatter = std::make_unique<Formatter_Terminal>();
            }
            _output->open_ostream( _name );
        }

        /**
         * Move Constructor
         */
        inline OutputConfiguration::OutputConfiguration( OutputConfiguration &&output_config ) :
            _output( std::move( output_config._output.release() ) ),
            _formatter( std::move( output_config._formatter.release() ) )
        {}

        /**
         * Sets the Output's log level
         * @param level Log level
         */
        inline void OutputConfiguration::setOutputLevel( LogLevel_types::Type level ) {
            _output_level = level;
        }

        /**
         * Sets the Output's log level
         * @param level Log level
         * @exception std::invalid_argument when argument is not a valid log level code
         */
        inline void OutputConfiguration::setOutputLevel( unsigned int level ) {
            if( level > 6 ) {
                throw new std::invalid_argument( "[OutputConfiguration::setOutputLevel( unsigned int )] level is not a valid log level." );
            } else {
                _output_level = LogLevel_types::getLevel( level );
            }
        }

        /**
         * Gets the output's log level code
         * @return Log level code
         */
        inline unsigned int OutputConfiguration::getOutputLevelCode() {
            return LogLevel_types::getCode( _output_level );
        }

        /**
         * Gets the Output's name
         * @return Name of the output
         */
        inline std::string OutputConfiguration::getName() {
            return _name;
        }

        /**
         * Sends message details to the formatter and then to the output
         * @param ts        TimeStamp of the message
         * @param msgNum    Message number in the session
         * @param msg       Log message
         */
        inline void OutputConfiguration::send( const TimeStamp &ts, const uint32_t &msgNum, const LogLevel_types::Type &level, const std::string &msg ) {
            std::string s = _formatter->formatMsg( ts, msgNum, level, msg );
            _output->write( s );
        }
    }
}

#endif //EADLIB_OUTPUT_CONFIGURATION_H
