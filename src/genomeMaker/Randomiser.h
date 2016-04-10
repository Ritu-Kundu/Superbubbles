#ifndef SUPERBUBBLES_RANDOMISER_H
#define SUPERBUBBLES_RANDOMISER_H

#include <random>

namespace genomeMaker {
    class Randomiser {
      public:
        Randomiser( const size_t &pool_size );
        unsigned int getRand();

      private:
        std::mt19937 _rng;
        std::uniform_int_distribution<uint32_t> _distribution;
    };
}

#endif //SUPERBUBBLES_RANDOMISER_H
