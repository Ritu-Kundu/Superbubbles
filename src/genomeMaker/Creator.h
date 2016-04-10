#ifndef SUPERBUBBLES_CREATOR_H
#define SUPERBUBBLES_CREATOR_H

//TODO DNA base pair generation (GC, AT)
//TODO RNA base pair generation (GC, UA, CG)
//TODO completely random generation from of a set of given letters

#include <iostream>
#include "Randomiser.h"
#include "ProgressDisplay.h"
#include "../../include/eadib_log/Logger.h"

namespace genomeMaker {
    class Creator {
      public:
        Creator( Randomiser &randomiser, const std::string &file_name  );
        void create_DNA( const uint64_t &genome_size );
        void create_RNA( const uint64_t &genome_size );
        void create_SET( const uint64_t &genome_size, const std::string &set );

      private:
        void createGenomeFile( const uint64_t &genome_size, const std::vector<char> &set  );
        std::string _file_name;
        Randomiser _randomiser;
    };
}

#endif //SUPERBUBBLES_CREATOR_H
