#ifndef EADLIB_LOGFORMATTER_TYPES_H
#define EADLIB_LOGFORMATTER_TYPES_H

#include <string>
#include <regex>

namespace eadlib {
    namespace log {
        struct Formatter_types {
            /**
             * Formatter types
             */
            enum class Type {
                TERMINAL
            };

            /**
             * Gets the description of a formatter type
             * @param type Formatter::Type
             * @return Description
             */
            inline static std::string getFormatterDescription( const Type &type ) {
                switch( type ) {
                    case Type::TERMINAL:
                        return "TERMINAL";
                }
            }

            /**
             * Gets the type of a formatter description
             * @param description Description
             * @return Type for the description
             * @exception throws std::invalid_argument when a descriptor doesn't match any of the formatter types
             */
            inline static Type getDescriptionType( const std::string &description ) {
                if( std::regex_match( description, std::regex( "TERMINAL" ))) {
                    return Type::TERMINAL;
                }
                throw std::invalid_argument( "Description doesn't match any log formatter types." );
            }
        };
    }
}
#endif //EADLIB_LOGFORMATTER_TYPES_H
