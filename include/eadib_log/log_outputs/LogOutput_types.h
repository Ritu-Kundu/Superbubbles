#ifndef EADLIB_LOGOUTPUT_TYPES_H
#define EADLIB_LOGOUTPUT_TYPES_H

#include <string>
#include <regex>

namespace eadlib {
    namespace log {
        struct LogOutput_types {
            /**
            * Output types available
            */
            enum class Type {
                FILE_OVERWRITE  ,
                FILE_APPEND     ,
                FILE_NEW        ,
                TERMINAL
            };

            /**
             * Gets the description of an output type
             * @param type LogOutput::Type
             * @return Description
             */
            inline static std::string getTypeDescription( const Type &type ) {
                switch( type ) {
                    case Type::FILE_OVERWRITE:
                        return "FILE_OVERWRITE";
                    case Type::FILE_APPEND:
                        return "FILE_APPEND";
                    case Type::FILE_NEW:
                        return "FILE_NEW";
                    case Type::TERMINAL:
                        return "TERMINAL";
                }
            }

            /**
             * Gets the type of an output description
             * @param description Description
             * @return Type for the description
             * @exception throws std::invalid_argument when a descriptor doesn't match any of the output types
             */
            inline static Type getDescriptionType( const std::string &description ) {
                if( std::regex_match( description, std::regex ( "FILE_OVERWRITE" ) ) ) {
                    return Type::FILE_OVERWRITE;
                }
                if( std::regex_match( description, std::regex ( "FILE_APPEND" ) ) ) {
                    return Type::FILE_APPEND;
                }
                if( std::regex_match( description, std::regex ( "FILE_NEW" ) ) ) {
                    return Type::FILE_NEW;
                }
                if( std::regex_match( description, std::regex ( "TERMINAL" ) ) ) {
                    return Type::TERMINAL;
                }
                throw std::invalid_argument( "Description doesn't match any log output types.");
            }
        };

    }
}
#endif //EADLIB_LOGOUTPUT_TYPES_H
