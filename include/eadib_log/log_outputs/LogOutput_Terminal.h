//
// Created by alwyn on 3/15/16.
//

#ifndef EADLIB_LOGOUTPUT_TERMINAL_H
#define EADLIB_LOGOUTPUT_TERMINAL_H

#include <iostream>
#include "LogOutput.h"

namespace eadlib {
    namespace log {
        class LogOutput_Terminal : public LogOutput {
          public:
            LogOutput_Terminal() {};
            ~LogOutput_Terminal() {};
            void open_ostream( const std::string &name );
            void close_ostream() { };
            void write( const std::string &msg );
          private:
            std::string _console_name;
        };
    }

    //-----------------------------------------------------------------------------------------------------------------
    // LogOutput_Terminal class method implementations
    //-----------------------------------------------------------------------------------------------------------------
    /**
     * Sets Console name
     * @param name Console name
     */
    inline void eadlib::log::LogOutput_Terminal::open_ostream( const std::string &name ) {
        this->_console_name = name;
    }


    /**
     * Writes to the console
     * @param msg Message to write
     */
    inline void eadlib::log::LogOutput_Terminal::write( const std::string &msg ) {
        std::cout << msg << std::endl;
    }
}

#endif //EADLIB_LOGOUTPUT_TERMINAL_H
