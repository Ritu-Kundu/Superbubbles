#include <iostream>

#include "../../include/eadib_log/Logger.h"
#include "Creator.h"
#include "tools/CLParser.h"


int main( int argc, char *argv[] ) {
    auto parser = genomeMaker::CLParser( argc, argv );
    if( parser.isValid() ) {
        std::cout << "|------------------------------------------|\n" <<
                     "|===========[Genome Maker v1.0]============|\n" <<
                     "|------------------------------------------|\n" <<
        std::endl;
        auto randomiser = genomeMaker::Randomiser();
        auto creator = genomeMaker::Creator( randomiser, parser.getFileName() );
        switch( parser.getType() ) {
            case genomeMaker::CLParser::LetterType::DNA:
                creator.create_DNA( parser.getGenomeSize() );
                break;
            case genomeMaker::CLParser::LetterType::RNA:
                creator.create_RNA( parser.getGenomeSize() );
                break;
            case genomeMaker::CLParser::LetterType::SET:
                creator.create_SET( parser.getGenomeSize(), parser.getLetterSet() );
                break;
        }

        //TODO Emulated FASTA reader
    }
    return 0;
}