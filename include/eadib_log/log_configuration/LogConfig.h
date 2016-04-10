//
// Created by alwyn on 3/15/16.
//

#ifndef EADLIB_LOG_CONFIG_H
#define EADLIB_LOG_CONFIG_H

#include <vector>
#include <regex>
#include <zconf.h>
#include "OutputConfiguration.h"
#include "LogLevel_types.h"
#include "../log_outputs/LogOutput_types.h"
#include "../log_formatters/Formatter_types.h"

namespace eadlib {
    namespace log {
        class LogConfig {
          public:
            LogConfig( const std::string &config_file_name );
            ~LogConfig() {};
            void createOutput( const std::string &name, const unsigned int &level, const LogOutput_types::Type &output_type,
                               const Formatter_types::Type &formatter_type );
            void distributeMsg( const TimeStamp &ts, const uint32_t &number_of_entries, const LogLevel_types::Type &event_type, const std::string &msg ) const;
          private:
            bool loadConfigLine( const std::string &line, const size_t &line_number );
            std::vector<std::string> extractArgs( const std::string &string );
            void loadDefaults();
            std::string getDefaultConfig();
            bool checkOutputNameExists( const std::string &name );
            std::string _config_file_name;
            std::vector<std::unique_ptr<OutputConfiguration>> _outputs;
        };

        //-----------------------------------------------------------------------------------------------------------------
        // Public "LogConfig" class method implementations
        //-----------------------------------------------------------------------------------------------------------------
        /**
         * Constructor
         * @param config_file_name Name of the configuration file
         */
        inline LogConfig::LogConfig( const std::string &config_file_name ) :
            _config_file_name( config_file_name )
        {
            if( access( _config_file_name.c_str(), F_OK ) != -1 ) { //file exists
                std::ifstream file;
                file.open( _config_file_name );
                std::string line { };
                size_t line_number = 0;
                while( std::getline( file, line ) ) {
                    line_number++;
                    if( !line.empty() ) {
                        if( !loadConfigLine( line, line_number ) ) {
                            std::cerr << "[LogConfig::loadConfigLine( " << line << ", " << line_number <<
                                " )] Line format unrecognised in the log configuration file. It will be ignored." << std::endl;
                        }
                    }
                }
                file.close();
            } else {
                loadDefaults();
                std::ofstream file;
                file.open( _config_file_name );
                file << getDefaultConfig();
                file.close();
            }
        }

        /**
         * Creates an Output path for the stream to go to
         * @param name           Name of output
         * @param level          Log level for output
         * @param output_type    Type of output
         * @param formatter_type Formatter for output
         */
        inline void LogConfig::createOutput( const std::string &name, const unsigned int &level, const LogOutput_types::Type &output_type,
                                      const Formatter_types::Type &formatter_type ) {
            if( !checkOutputNameExists( name ) ) {
                try {
                    this->_outputs.push_back( std::unique_ptr<OutputConfiguration>( new OutputConfiguration( name,
                                                                                                             LogLevel_types::getLevel( level ),
                                                                                                             output_type,
                                                                                                             formatter_type ) ) );
                } catch ( std::invalid_argument e ) {
                    std::cerr << "'" << level << "' is not a valid log level code." << std::endl;
                }
            } else {
                std::cerr << "[eadlib::Logger::createOutput( " << name << ", " << level << ", " <<
                    LogOutput_types::getTypeDescription( output_type ) << ", " << Formatter_types::getFormatterDescription( formatter_type ) <<
                    " )] Output name already exists. Output will not be created." << std::endl;
            }
        }

        /**
         * Distributes a log message to the available outputs
         * @param ts                Time stamp of the message
         * @param number_of_entries Message number in session
         * @param event_type        Message level
         * @param msg               Message description
         */
        inline void LogConfig::distributeMsg( const TimeStamp &ts, const uint32_t &number_of_entries, const LogLevel_types::Type &event_type, const std::string &msg ) const {
            for( auto const &output_option : _outputs ) {
                if( output_option->getOutputLevelCode() > 0 && output_option->getOutputLevelCode() >= LogLevel_types::getCode( event_type ) ) {
                    try {
                        output_option->send( TimeStamp(), number_of_entries, event_type, msg);
                    }
                    catch( const std::exception &e ) {
                        std::cout << e.what();
                    }
                }
            }
        }

        //-----------------------------------------------------------------------------------------------------------------
        // Private "LogConfig" class method implementations
        //-----------------------------------------------------------------------------------------------------------------
        /**
         * Checks and loads a config line
         * @param line Configuration line to check & load
         * @return Success
         */
        inline bool LogConfig::loadConfigLine( const std::string &line, const size_t &line_number ) {
            std::string cfg_line = line;
            cfg_line.erase( std::remove_if( cfg_line.begin(), cfg_line.end(), isspace ), cfg_line.end() ); //loose any whitespace in the line
            std::regex rx_comment_line ( "//(.*?)"); //Regex for comment line
            std::regex rx_output_desc ( "OUTPUT=\\<(.*?)\\>" ); //Regex for output descriptor line
            if( std::regex_match( cfg_line, rx_comment_line ) ) {
                return true;
            } else if( std::regex_match( cfg_line, rx_output_desc ) ) {
                std::vector<std::string> args = extractArgs( cfg_line );
                if( args.size() == 4 ) {
                    try {
                        auto output = LogOutput_types::getDescriptionType( args.at( 1 ) );
                        auto formatter = Formatter_types::getDescriptionType( args.at( 2 ) );
                        auto level = LogLevel_types::getDescriptionType( args.at( 3 ) );
                        createOutput( args.at(0), LogLevel_types::getCode( level ), output , formatter );
                        return true;
                    } catch ( std::invalid_argument ) {
                        std::cerr << "[LogConfig::loadConfigLine( " << line << ", " << line_number << " )] Unsupported argument(s)." << std::endl;
                        return false;
                    }
                }
            }
            return false;
        }

        /**
         * Loads hard coded default
         */
        inline void LogConfig::loadDefaults() {
            createOutput( "log", 6, eadlib::log::LogOutput_types::Type::FILE_NEW, eadlib::log::Formatter_types::Type::TERMINAL );
            createOutput( "console", 3, eadlib::log::LogOutput_types::Type::TERMINAL, eadlib::log::Formatter_types::Type::TERMINAL );
        }

        /**
         * Gets the default config file content string
         * @return String of all the defaults
         */
        inline std::string LogConfig::getDefaultConfig() {
            std::stringstream ss;
            ss << "//===================================LOG CONFIG FILE=========================================//\n" <<
            "// Available outputs:    { TERMINAL, FILE_APPEND, FILE_OVERWRITE, FILE_NEW }\n" <<
            "// Available formatters: { TERMINAL }\n" <<
            "// Available log levels: { FATAL, ERROR, WARNING, MSG, DEBUG, TRACE }\n" <<
            "//-------------------------------------------------------------------------------------------//\n" <<
            "// Note: Spaces are truncated automatically.\n" <<
            "//       Any lines starting with '//' are treated as comments.\n" <<
            "//-------------------------------------------------------------------------------------------//\n" <<
            "// Config format: \"OUTPUT=<output/file name,output,formatter,log level>\"\n" <<
            "//          e.g.: OUTPUT=<my_log, FILE_NEW, TERMINAL, MSG>\n" <<
            "//===========================================================================================//\n" <<
            "OUTPUT=<log,FILE_NEW,TERMINAL,WARNING>\n" <<
            "OUTPUT=<console,TERMINAL,TERMINAL,TRACE>\n";
            return ss.str();
        }

        /**
         * Checks if a output name already exists in the output vector
         * @param name Name to check
         * @return Existence
         */
        inline bool LogConfig::checkOutputNameExists( const std::string &name ) {
            for( auto &out : _outputs ) {
                if( out->getName() == name ) {
                    return true;
                }
            }
            return false;
        }

        /**
        * Extracts the arguments in the string into a vector
        * @param string String to extract from
        * @return Vector of all arguments extracted
        */
        inline std::vector<std::string> LogConfig::extractArgs( const std::string &string ) {
            size_t cut_begin = string.find( "<" );
            size_t cut_end = string.find( ">" );
            std::string temp = string.substr( cut_begin + 1, cut_end - ( cut_begin + 1 ) );
            std::vector<std::string> args;
            cut_begin = 0;
            while( cut_end != temp.npos ) {
                cut_end = temp.find( ",", cut_begin );
                if( cut_end - cut_begin == temp.npos ) cut_end = temp.size();
                args.emplace_back( temp.substr( cut_begin, cut_end - cut_begin ) );
                cut_begin = cut_end + 1;
            }
            return args;
        }
    }
}

#endif //EADLIB_LOG_CONFIG_H
