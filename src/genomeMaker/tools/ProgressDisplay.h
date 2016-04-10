#ifndef SUPERBUBBLES_PROGRESSDISPLAY_H
#define SUPERBUBBLES_PROGRESSDISPLAY_H

#include <iostream>

namespace genomeMaker {
    class ProgressDisplay {
      public:
        ProgressDisplay( const uint64_t &total_steps, const unsigned int &width );
        void update( const uint64_t &current_step );

      private:
        double calculatePercent( const uint64_t &current_step );
        uint64_t calculatePosition( const uint64_t &current_step );
        uint64_t _total_steps;
        unsigned int _size;
    };
}

#endif //SUPERBUBBLES_PROGRESSDISPLAY_H