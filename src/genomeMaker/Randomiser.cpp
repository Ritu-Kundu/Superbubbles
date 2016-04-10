//
// Created by alwyn on 4/9/16.
//

#include "Randomiser.h"

/**
 * Constructor
 */
genomeMaker::Randomiser::Randomiser( const size_t &pool_size ) {
    _rng.seed( uint32_t() );
    _distribution = std::uniform_int_distribution<uint32_t>( 0, pool_size );
}

/**
 * Gets a random number from the pool
 * @return Random number from pool
 */
unsigned int genomeMaker::Randomiser::getRand() {
    return _distribution( _rng );
}



