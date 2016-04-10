#ifndef SUPERBUBBLES_RANDOMISER_H
#define SUPERBUBBLES_RANDOMISER_H

#include <random>
#include "eadib_log/Logger.h"

namespace genomeMaker {
    class Randomiser {
      public:
        Randomiser();
        Randomiser( const Randomiser &randomiser );
        Randomiser( Randomiser &&randomiser );
        bool setPoolRange( const uint64_t &range_from, const uint64_t &range_to );
        unsigned long getRand();
      private:
        std::mt19937 _rng;
        std::uniform_int_distribution<uint64_t> _distribution;
    };
}

#endif //SUPERBUBBLES_RANDOMISER_H
