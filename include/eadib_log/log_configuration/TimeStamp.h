#ifndef EADLIB_TIMESTAMP_H
#define EADLIB_TIMESTAMP_H

#include <iostream>
#include <chrono>
#include <iomanip>

namespace eadlib {
    namespace log {
        /**
         * TimeStamp
         * @brief object containing the time/date details of its creation
         */
        class TimeStamp {
          public:
            TimeStamp();
            ~TimeStamp() {};
            std::string getTime() const;
            std::string getDate() const;
            std::string getTimeStamp( const std::string &formatter ) const;
          private:
            std::time_t _time_stamp;
        };

        /**
         * Constructor
         */
        inline TimeStamp::TimeStamp() :
            _time_stamp( std::chrono::system_clock::to_time_t( std::chrono::system_clock::now() ) )
        {}

        /**
         * Gets the time as a string
         * @return time stamp
         */
        inline std::string TimeStamp::getTime() const {
            std::stringstream ss;
            ss << std::put_time( std::localtime(&_time_stamp ), "%H:%M:%S");
            return ss.str();
        }

        /**
         * Gets the date as a string
         * @return date stamp
         */
        inline std::string TimeStamp::getDate() const {
            std::stringstream ss;
            ss << std::put_time( std::localtime( &_time_stamp ), "%d/%m/%Y");
            return ss.str();
        }

        /**
         * Gets the time stamp as a string
         * @param formatter Formatter string for the output
         * @return Formatted time stamp
         */
        inline std::string TimeStamp::getTimeStamp( const std::string &formatter ) const {
            std::stringstream ss;
            ss << std::put_time( std::localtime( &_time_stamp ), formatter.c_str() );
            return ss.str();
        }
    }
}

#endif //EADLIB_TIMESTAMP_H
