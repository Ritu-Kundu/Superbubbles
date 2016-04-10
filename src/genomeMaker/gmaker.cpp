#include <iostream>
#include "../../include/eadib_log/Logger.h"
#include "Creator.h"

/**
 * Prints the command line argument usage
 */
void printCmdUsage( const int &argc, char *argv[] ) {
    LOG_TRACE( "Usage :", argv[0] );
    std::cout << "Usage: " << argv[0] << " <size> <filename>" << std::endl;
}

int main( int argc, char *argv[] ) {
    auto randomiser = genomeMaker::Randomiser();
    auto creator = genomeMaker::Creator( randomiser, "test" );
    creator.create_DNA( 100000 );

    /*
    if ( argc != 2 ) // argc should be 2 for correct execution
        printCmdUsage( argc, argv );
    else {
        /*
        // We assume argv[1] is a filename to open
        ifstream the_file ( argv[1] );
        // Always check to see if file opening succeeded
        if ( !the_file.is_open() )
            cout<<"Could not open file\n";
        else {
            char x;
            // the_file.get ( x ) returns false if the end of the file
            //  is reached or an error occurs
            while ( the_file.get ( x ) )
                cout<< x;
        }
        // the_file is closed implicitly here
    }
         */
    return 0;
}