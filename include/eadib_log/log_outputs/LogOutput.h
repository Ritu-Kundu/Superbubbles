//
// Created by alwyn on 3/15/16.
//

#ifndef EADLIB_LOGOUTPUT_H
#define EADLIB_LOGOUTPUT_H

#include <iostream>

namespace eadlib {
    namespace log {
        class LogOutput {
          public:
            virtual void open_ostream( const std::string &name ) = 0;
            virtual void close_ostream() = 0;
            virtual void write( const std::string &msg ) = 0;
        };
    }
}
#endif //EADLIB_LOGOUTPUT_H
