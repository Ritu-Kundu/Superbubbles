#ifndef SUPERBUBBLES_CREATOR_H
#define SUPERBUBBLES_CREATOR_H

//TODO DNA base pair generation (GC, AT)
//TODO RNA base pair generation (GC, UA, CG)
//TODO completely random generation from of a set of given letters

#include <iostream>
#include "Randomiser.h"
#include "../../include/eadib_log/Logger.h"

namespace genomeMaker {
    class Creator {
      public:
        Creator( const std::string &file_name  );
        void create_DNA() const;
        void create_RNA() const;
        void create_SET( const std::string &set ) const;

      private:
        std::string _file_name;
    };
}

#endif //SUPERBUBBLES_CREATOR_H
