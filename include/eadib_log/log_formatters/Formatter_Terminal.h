#ifndef EADLIB_FORMATTER_TERM_H
#define EADLIB_FORMATTER_TERM_H

#include <sstream>
#include "Formatter.h"

namespace eadlib {
    namespace log {
        /**
         * Formatter for the terminal output
         */
        class Formatter_Terminal : public Formatter {
          public:
            Formatter_Terminal() {};
            ~Formatter_Terminal() {};
            std::string formatMsg( const TimeStamp &ts, const uint32_t &msgNum, const LogLevel_types::Type &level, const std::string &msg );
          protected:
            std::string formatMsgNumber( const uint32_t &msgNum );
            std::string formatMsgLevel( const LogLevel_types::Type &level );
        };

        //-----------------------------------------------------------------------------------------------------------------
        // Public "Formatter_TERM" class method implementations
        //-----------------------------------------------------------------------------------------------------------------
        /**
         * Formats the message for console output
         * @param ts        TimeStamp of the message
         * @param msgNum    Message's number in the session
         * @param msg       Log message
         * @return formatted output string stream
         */
        inline std::string Formatter_Terminal::formatMsg( const TimeStamp &ts, const uint32_t &msgNum, const LogLevel_types::Type &level, const std::string &msg ) {
            std::stringstream line;
            line << "[";
            line << formatMsgNumber( msgNum );
            line << "] ";
            line << ts.getDate() << " - " << ts.getTime() << " ";
            line << formatMsgLevel( level );
            line << msg;
            return line.str();
        }

        //-----------------------------------------------------------------------------------------------------------------
        // Private "Formatter_TERM" class method implementations
        //-----------------------------------------------------------------------------------------------------------------
        /**
         * Formats the message's session number for output
         * @param msgNum Message session number
         * @return Formatted string
         */
        inline std::string Formatter_Terminal::formatMsgNumber( const uint32_t &msgNum ) {
            std::ostringstream oss;
            oss.fill( '0' );
            oss.width( 7 );
            oss << msgNum;
            return oss.str();
        }

        /**
         * Formats the message's log level
         * @param level Log level
         * @return Formatted string
         */
        inline std::string Formatter_Terminal::formatMsgLevel( const LogLevel_types::Type &level ) {
            switch( level ) {
                case LogLevel_types::Type::FATAL:
                    return "|--FATAL--| ";
                case LogLevel_types::Type::ERROR:
                    return "|--ERROR--| ";
                case LogLevel_types::Type::WARNING:
                    return "|-WARNING-| ";
                case LogLevel_types::Type::MSG:
                    return "|-MESSAGE-| ";
                case LogLevel_types::Type::DEBUG:
                    return "|--DEBUG--| ";
                case LogLevel_types::Type::TRACE:
                    return "|--TRACE--| ";
                case LogLevel_types::Type::OFF:
                    return "|---OFF---| ";
            }
        }
    }
}

#endif //EADLIB_FORMATTER_TERM_H
