#ifndef SUPERBUBBLES_CLPARSER_H
#define SUPERBUBBLES_CLPARSER_H

#include <iostream>
#include <regex>
#include <unordered_map>
#include "../../../include/eadib_log/Logger.h"

namespace genomeMaker {
    class CLParser {
      public:
        enum class LetterType {
            DNA,
            RNA,
            SET
        };
        CLParser( const int &argc, char *argv[] );
        static void printInfo( const int &argc, char *argv[] );
        bool isValid();
        std::string getFileName();
        uint64_t getGenomeSize();
        LetterType getType();
        std::string getLetterSet();

      private:
        bool parseFileName( const std::string &s );
        bool parseGenomeSize( const std::string &s );
        bool parseGenomeType( const std::string &s );
        bool parseLetterSet( const std::string &s );
        bool _valid_flag;
        std::pair<bool, std::string> _file_name { false, "" };
        std::pair<bool, LetterType> _genome_type { false, LetterType::DNA };
        std::pair<bool, uint64_t> _genome_size { false, 0 };
        std::pair<bool, std::string> _letter_set { false, "" };
    };
}

#endif //SUPERBUBBLES_CLPARSER_H
