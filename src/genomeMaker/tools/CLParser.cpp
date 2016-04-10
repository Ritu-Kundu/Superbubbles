#include "CLParser.h"

/**
 * Constructor
 * @param argc Argument count
 * @param argv Argument variables
 */
genomeMaker::CLParser::CLParser( const int &argc, char *argv[] ) :
    _valid_flag( false )
{
    if( argc < 2 ) {
        printInfo( argc, argv );
    } else {
        std::vector<std::string> arguments;
        for( int i = 1; i < argc; i++ ) {
            arguments.emplace_back( argv[ i ] );
        }
        //Might be a std file + size format with no flag
        if( arguments.size() == 2 ) {
            if( parseFileName( arguments.at( 0 ) ) && parseGenomeSize( arguments.at( 1 ) ) ) {
                _valid_flag = true;
                return;
            } else {
                _file_name.first = false;
                _genome_size.first = false;
            }
        }
        //Multi flag and arguments
        std::vector<std::string>::iterator it = arguments.begin();
        while( it != arguments.end() ) {
            if( std::regex_match( *it, std::regex( "-s" ) ) ) { //Genome size
                it++;
                if( it != arguments.end() && !parseGenomeSize( *it )) return;
            } else if( std::regex_match( *it, std::regex( "-o" ) ) ) { //File name
                it++;
                if( it != arguments.end() && !parseFileName( *it ) ) return;
            } else if( std::regex_match( *it, std::regex( "-t" ) ) ) { //Genome type & letter set if type == SET
                it++;
                if( it != arguments.end() && parseGenomeType( *it ) ) {
                    if( getType() == LetterType::SET ) {
                        it++;
                        if( it == arguments.end() ) {
                            LOG_ERROR( "[genomeMaker::CLParser::CLParser(..)] \'-t SET\' flag given but no letters set was found after." );
                        } else if( !parseLetterSet( *it ) ) {
                            LOG_ERROR( "[genomeMaker::CLParser::CLParser(..)] \'-t SET\' flag given but no letters set was found after." );
                            return;
                        }
                    }
                }
            } else if( std::regex_match( *it, std::regex( "-h" ) ) ) { //help
                printInfo( argc, argv );
                return;
            } else {
                LOG_ERROR( "[genomeMaker::CLParser::CLParser(..)] Argument \'", *it, "\' is not recognised." );
                return;
            }
            it++;
        }
        if( !_file_name.first ) _file_name = { true, "genome" };
        if( !_genome_type.first ) _genome_type = { true, LetterType::DNA };
        if( _genome_size.first ) _valid_flag = true;
    }
}

/**
 * Prints the command line argument usage
 * @param argc Argument count
 * @param argv Argument variables
 */
void genomeMaker::CLParser::printInfo( const int &argc, char *argv[] ) {
    std::cout <<
        "-USAGE-\n" <<
        "\t" << argv[0] << " <filename> <size>\n" <<
        "\t" << argv[0] << " -<flag> <argument>\n" <<
        "\n-FLAGS-\n" <<
        "\t-s <size>\t[Size of the genome]\n" <<
        "\t-o <filename>\t[File name for the synthetic genome and FASTA file]\n" <<
        "\t-t <type>\t[Default to DNA if not used. Types: { DNA, RNA, SET }]\n" <<
        "\n-EXAMPLES-\n" <<
        "\t" << argv[0] << " genome_file 100000\n"
        "\t" << argv[0] << " -o genome_file -s 100000\n" <<
        "\t" << argv[0] << " -o genome_file -s 100000 -t RNA\n" <<
        "\t" << argv[0] << " -o genome_file -s 100000 -t SET ABCDEFG\n" <<
    std::endl;
}

/**
 * Gets the validity of the parsed arguments
 * @return Validity
 */
bool genomeMaker::CLParser::isValid() {
    return _valid_flag;
}

std::string genomeMaker::CLParser::getFileName() {
    return _file_name.second;
}

uint64_t genomeMaker::CLParser::getGenomeSize() {
    return _genome_size.second;
}

genomeMaker::CLParser::LetterType genomeMaker::CLParser::getType() {
    return _genome_type.second;
}

std::string genomeMaker::CLParser::getLetterSet() {
    return _letter_set.second;
}

/**
 * Parses the file name
 * @param s String containing the file name contender
 * @return Success
 */
bool genomeMaker::CLParser::parseFileName( const std::string &s ) {
    if( _file_name.first ) {
        LOG_ERROR( "[genomeMaker::CLParser::parseFileName( ", s, " )] File name was already processed. Possible duplicate arguments." );
        return false;
    }
    if( s.find( '\t' ) != s.npos || s.find( ' ' ) != s.npos ) return false;
    _file_name = { true, s };
    return true;
}

/**
 * Parse the genome size
 * @param s String containing the size
 * @return Success
 */
bool genomeMaker::CLParser::parseGenomeSize( const std::string &s ) {
    if( _genome_size.first ) {
        LOG_ERROR( "[genomeMaker::CLParser::parseGenomeSize( ", s, " )] Genome size was already processed. Possible duplicate arguments." );
        return false;
    }
    std::stringstream ss { s };
    uint64_t convertedSize;
    if( !( ss >> convertedSize )) {
        LOG_ERROR( "[genomeMaker::CLParser::parseGenomeSize(", s, ")] Not a valid unsigned long received." );
        return false;
    }
    _genome_size = { true, convertedSize };
    return true;
}

/**
 * Parses the genome type
 * @param s String containing the genome type
 * @return Success
 */
bool genomeMaker::CLParser::parseGenomeType( const std::string &s ) {
    if( _genome_type.first ) {
        LOG_ERROR( "[genomeMaker::CLParser::parseGenomeType( ", s, " )] Genome type was already processed. Possible duplicate arguments." );
        return false;
    }
    if( std::regex_match( s, std::regex( "DNA" ) ) || std::regex_match( s, std::regex( "dna" ) ) ) {
        _genome_type = { true, LetterType::DNA };
        return true;
    }
    if( std::regex_match( s, std::regex( "RNA" ) ) || std::regex_match( s, std::regex( "rna" ) ) ) {
        _genome_type = { true, LetterType::RNA };
        return true;
    }
    if( std::regex_match( s, std::regex( "SET" ) ) || std::regex_match( s, std::regex( "set" ) ) ) {
        _genome_type = { true, LetterType::SET };
        return true;
    }
    return false;
}

/**
 * Parses the custom genome letter set
 * @param s String containing the letter set
 * @return Success
 */
bool genomeMaker::CLParser::parseLetterSet( const std::string &s ) {
    if( _letter_set.first ) {
        LOG_ERROR( "[genomeMaker::CLParser::parseLetterSet( ", s, " )] Letter set was already processed. Possible duplicate arguments." );
        return false;
    }
    if( s.find( '\t' ) != s.npos || s.find( ' ' ) != s.npos || s.size() < 1 ) return false;
    _letter_set = { true, s };
    return true;
}




















