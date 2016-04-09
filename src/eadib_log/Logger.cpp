//
// Created by Alwlyan on 21/06/2015.
//

#include <sstream>
#include <fstream>
#include <algorithm>
#include "Logger.h"

///*********************************************************************
/// Logger [Public methods]
///*********************************************************************
/**
 * Logger Constructor
 */
eadlib::log::Logger::Logger() :
    _number_of_entries( 0 ),
    _config( std::make_unique<eadlib::log::LogConfig>( "log_config.cfg" ) )
{}

///*********************************************************************
/// Logger [Private methods]
///*********************************************************************


/**
 * Gets the current log entry number
 * @return Entry number
 */
std::string eadlib::log::Logger::getEntryNumber() {
    std::stringstream ss;
    ss.fill( '0' );
    ss.width( 7 );
    ss << this->_number_of_entries;
    return ss.str();
}
