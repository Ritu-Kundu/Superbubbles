//
// Created by alwyn on 4/9/16.
//

#include "Randomiser.h"

/**
 * Constructor
 * Note: default pool range is 0-1 (coin flip)
 */
genomeMaker::Randomiser::Randomiser() {
    setPoolRange( 0, 1 );
}

/**
 * Copy-Constructor
 * @param randomiser Randomiser to copy
 */
genomeMaker::Randomiser::Randomiser( const Randomiser &randomiser ) :
    _rng( randomiser._rng ),
    _distribution( randomiser._distribution )
{}

/**
 * Move-Constructor
 * @param randomiser Randomiser to move over
 */
genomeMaker::Randomiser::Randomiser( Randomiser &&randomiser ) :
    _rng( std::move( randomiser._rng ) ),
    _distribution( std::move( randomiser._distribution ) )
{}

/**
 * Gets a random number from the pool
 * @return Random number from pool
 */
unsigned long genomeMaker::Randomiser::getRand() {
    return _distribution( _rng );
}

/**
 * Sets the randomiser to a new pool size
 * @param range_from Lower bound of the pool range
 * @param range_to   Upper bound of the pool range
 * @return Success
 */
bool genomeMaker::Randomiser::setPoolRange( const uint64_t &range_from, const uint64_t &range_to ) {
    if( ( range_to - range_from ) < 1 ) {
        LOG_ERROR( "[genomeMaker::Randomiser::setPoolSize( ", range_from, ", ", range_to, " )] Pool size specified is too small (", range_to - range_from, ")." );
        return false;
    }
    _rng.seed( uint64_t() );
    _distribution = std::uniform_int_distribution<uint64_t>( range_from, range_to );
    return true;
}
