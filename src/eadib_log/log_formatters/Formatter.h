//
// Created by alwyn on 3/15/16.
//

#ifndef EADLIB_FORMATTER_H
#define EADLIB_FORMATTER_H

#include <stdint.h>
#include <iostream>
#include "../log_configuration/TimeStamp.h"
#include "../log_configuration/LogLevel_types.h"

namespace eadlib {
    namespace log {
        /**
         * Message Formatter interface
         */
        class Formatter {
          public:
            virtual std::string formatMsg( const TimeStamp &ts, const uint32_t &msgNum, const LogLevel_types::Type &level, const std::string &msg ) = 0;
          protected:
            virtual std::string formatMsgNumber( const uint32_t &msgNum ) = 0;
            virtual std::string formatMsgLevel( const LogLevel_types::Type &level ) = 0;
        };
    }
}

#endif //EADLIB_FORMATTER_H
