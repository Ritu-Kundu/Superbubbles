#include <iomanip>
#include "ProgressDisplay.h"

/**
 * Constructor
 * @param total_steps Total number of steps over the progress
 * @param width       Width of the graphical progress bar in the console
 */
genomeMaker::ProgressDisplay::ProgressDisplay( const uint64_t &total_steps, const unsigned int &width ) :
    _total_steps( total_steps ),
    _size( width )
{}

/**
 * Updates the progress bar
 * @param current_step Current step in the progress
 */
void genomeMaker::ProgressDisplay::update( const uint64_t &current_step ) {
    uint64_t position = calculatePosition( current_step );
    double percentage = calculatePercent( current_step );

    if( current_step == 1 ) {
        std::cout << "\r";
    }
    std::cout << "[";
    for( int i = 1; i < position; i++ ) {
        std::cout << "=";
    }
    if( current_step == _total_steps ) {
        std::cout << "] " << "Done.     " << std::endl;
    } else {
        if( position < _size ) {
            std::cout << "|";
        }
        for( uint64_t i = position; i < _size - 1; i++ ) {
            std::cout << " ";
        }
        std::cout << "] " << std::fixed << std::setprecision( 3 ) << percentage << "\%\r";
    }
}

/**
 * Calculates the percentage of the progress
 * @param current_step Current step in the progress
 * @return Progress percentage
 */
double genomeMaker::ProgressDisplay::calculatePercent( const uint64_t &current_step ) {
    return (double) current_step * 100 / (double)_total_steps;
}

/**
 * Calculates the position on the progress bar
 * @param current_step Current step in the progress
 * @return Progress bar position
 */
uint64_t genomeMaker::ProgressDisplay::calculatePosition( const uint64_t &current_step ) {
    return current_step * _size / _total_steps;
}