#include "Creator.h"

/**
 * Constructor
 * @param file_name File name
 */
genomeMaker::Creator::Creator( const std::string &file_name ) :
    _file_name( file_name )
{}

/**
 * Creates a DNA genome
 */
void genomeMaker::Creator::create_DNA() const {
    std::vector<char> letters = { 'A', 'C','G', 'T' };
    Randomiser r = Randomiser( letters.size() - 1 );
    for( int i = 0; i < 100; i++ ) {
        LOG_TRACE( "Got ", r.getRand(), " from random pool.");
    }

}

/**
 * Creates a RNA genome
 */
void genomeMaker::Creator::create_RNA() const {

}

/**
 * Creates a genome from a set of letters
 * @param set Set of letters to use to create genome
 */
void genomeMaker::Creator::create_SET( const std::string &set ) const {

}







