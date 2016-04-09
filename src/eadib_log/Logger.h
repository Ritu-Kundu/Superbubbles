//
// Created by Alwlyan on 21/06/2015.
//

#ifndef EADLIB_LOGGER_H
#define EADLIB_LOGGER_H

#include <iostream>
#include <sstream>
#include <vector>
#include <exception>
#include <mutex>
#include "log_outputs/LogOutput.h"
#include "log_configuration/LogLevel_types.h"
#include "log_configuration/OutputConfiguration.h"
#include "log_configuration/LogConfig.h"

#ifndef NDEBUG
    #define LOG_FATAL eadlib_logger_instance.print< eadlib::log::LogLevel::Type::FATAL >
    #define LOG_ERROR eadlib_logger_instance.print< eadlib::log::LogLevel_types::Type::ERROR >
    #define LOG_WARNING eadlib_logger_instance.print< eadlib::log::LogLevel_types::Type::WARNING >
    #define LOG eadlib_logger_instance.print< eadlib::log::LogLevel_types::Type::MSG >
    #define LOG_DEBUG eadlib_logger_instance.print< eadlib::log::LogLevel_types::Type::DEBUG >
    #define LOG_TRACE eadlib_logger_instance.print< eadlib::log::LogLevel_types::Type::TRACE >
#else
    #define LOG_FATAL eadlib_logger_instance.print< eadlib::log::LogLevel::Type::FATAL >
    #define LOG_ERROR eadlib_logger_instance.print< eadlib::log::LogLevel::Type::ERROR >
    #define LOG_WARNING eadlib_logger_instance.print< eadlib::log::LogLevel::Type::WARNING >
    #define LOG(...)
    #define LOG_DEBUG(...)
    #define LOG_TRACE(...)
#endif

namespace eadlib {
    namespace log {
        class Logger {
          public:
            Logger();
            ~Logger() { };
            //Logging
            template<eadlib::log::LogLevel_types::Type event_type, typename...Args> void print( Args...args );
            template<eadlib::log::LogLevel_types::Type event_type> void print_();
            template<eadlib::log::LogLevel_types::Type event_type, typename H, typename...T> void print_( H head, T...tail );
          private:
            std::mutex _mutex;
            uint32_t _number_of_entries;
            std::stringstream _log_stream;
            std::unique_ptr<LogConfig> _config;
            //Private Methods
            std::string getEntryNumber();
        };

        //-----------------------------------------------------------------------------------------------------------------
        // Logger class method implementations
        //-----------------------------------------------------------------------------------------------------------------
        /**
         * Prints log message
         * @param args Arguments in message
         */
        template<eadlib::log::LogLevel_types::Type event_type, typename...Args> void Logger::print( Args...args ) {
            _mutex.lock();
            Logger::print_<event_type>( args... );
            _mutex.unlock();
        };

        /**
         * Print helper [end function for recursion]
         */
        template<eadlib::log::LogLevel_types::Type event_type> void Logger::print_() {
            _config->distributeMsg( TimeStamp(), _number_of_entries, event_type, _log_stream.str() );
            _number_of_entries++;
            _log_stream.str( std::string()); //emptying string stream
        }

        /**
         * Print helper [recursive function]
         * @param head Head of the list of arguments
         * @pram tail Rest of the list of arguments
         */
        template<eadlib::log::LogLevel_types::Type event_type, typename H, typename...T> void Logger::print_( H head, T...tail ) {
            _log_stream << head;
            print_<event_type>( tail... );
        };
    }
}

static eadlib::log::Logger eadlib_logger_instance;

#endif //EADLIB_LOGGER_H
