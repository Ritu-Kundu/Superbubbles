#ifndef EADLIB_LOGLEVEL_TYPES_H
#define EADLIB_LOGLEVEL_TYPES_H

#include <string>
#include <regex>

namespace eadlib {
    namespace log {
        struct LogLevel_types {
            /**
             * Enum of logging level types available
             */
            enum class Type {
                OFF,        //Logging is off
                FATAL,      //Fatal messages are logged
                ERROR,      //Error messages and above are logged
                WARNING,    //Warning messages and above are logged
                MSG,        //Standard messages and above are logged
                DEBUG,      //Debug messages and above are logged
                TRACE       //Trace messages and above are logged
            };

            /**
             * Gets the code for the log level type
             * @param level Log level enum type
             * @return Level code
             */
            inline static unsigned int getCode( const Type &level ) {
                switch( level ) {
                    case Type::OFF:
                        return 0;
                    case Type::FATAL:
                        return 1;
                    case Type::ERROR:
                        return 2;
                    case Type::WARNING:
                        return 3;
                    case Type::MSG:
                        return 4;
                    case Type::DEBUG:
                        return 5;
                    case Type::TRACE:
                        return 6;
                }
            }

            /**
             * Gets the type for the level code
             * @param code Code to get the type for
             * @return Log level type
             * @throws std::invalid_argument when the code is not a valid log level
             */
            inline static Type getLevel( const unsigned int &code ) {
                switch( code ) {
                    case 0:
                        return Type::OFF;
                    case 1:
                        return Type::FATAL;
                    case 2:
                        return Type::ERROR;
                    case 3:
                        return Type::WARNING;
                    case 4:
                        return Type::MSG;
                    case 5:
                        return Type::DEBUG;
                    case 6:
                        return Type::TRACE;
                    default:
                        throw std::invalid_argument( "The code passed is not a valid log level." );
                }
            }

            /**
             * Gets the type of a level description
             * @param description Description
             * @return Type for the description
             * @exception throws std::invalid_argument when a descriptor doesn't match any of the log level types
             */
            inline static Type getDescriptionType( const std::string &description ) {
                if( std::regex_match( description, std::regex( "FATAL" ))) {
                    return Type::FATAL;
                }
                if( std::regex_match( description, std::regex( "ERROR" ))) {
                    return Type::ERROR;
                }
                if( std::regex_match( description, std::regex( "WARNING" ))) {
                    return Type::WARNING;
                }
                if( std::regex_match( description, std::regex( "MSG" ))) {
                    return Type::MSG;
                }
                if( std::regex_match( description, std::regex( "DEBUG" ))) {
                    return Type::DEBUG;
                }
                if( std::regex_match( description, std::regex( "TRACE" ))) {
                    return Type::TRACE;
                }

                throw std::invalid_argument( "Description doesn't match any log level types." );
            }
        };
    }
}

#endif //EADLIB_LOGLEVEL_TYPES_H
