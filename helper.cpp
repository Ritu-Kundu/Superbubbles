/**
    Superbubbles
    Copyright (C) 2016 Ritu Kundu, Fatima Vayani, Manal Mohamed, Solon P. Pissis 
    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.
    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.
    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
**/

/** Defines some helper functions */

#include "helperDefs.hpp"

namespace supbub{

  static struct option long_options[] =
    {
      { "input-file",              required_argument, NULL, 'i' },
      { "output-file",             required_argument, NULL, 'o' },
      { "help",                    no_argument,       NULL, 'h' },
      { NULL,                      0,                 NULL, 0   }
    };

  /** Decode the input flags
   */
  int 
  decodeFlags(int argc, char* argv [], struct InputFlags* flags){
    int oi;
    int opt;
    int val;
    char* ep;
    int args;  
    /* initialisation */
    flags -> input_filename = NULL;
    flags -> output_filename = NULL;
    while ((opt = getopt_long(argc, argv, "i:o:h", long_options, &oi)) != - 1) {
      switch (opt) {
      case 'i':
	{
	  std::string inFile(optarg);
	  flags->input_filename = new char[inFile.size() + 1];
	  inFile.copy(flags->input_filename, inFile.size());
	  args ++;
	  break;
	}

      case 'o':
	{
	  std::string outFile(optarg);
	  flags->output_filename = new char[outFile.size() + 1];
	  outFile.copy(flags->output_filename, outFile.size());
	  args ++;
	  break;
	}

      case 'h':
	return (0);
      }
    }
    if ( args < 2 ){
      return (0);
    }
    else{
      return (optind);
    }
  }

  /* 
   * Usage of the tool 
   */
  void 
  usage(void){
    fprintf ( stdout, " Usage: supbub <options>\n" );
    fprintf ( stdout, " Standard (Mandatory):\n" );
    fprintf ( stdout, "  -i, --input-file          <str>     Input file  name.\n" );
    fprintf ( stdout, "  -o, --output-file         <str>     Output filename.\n" );
  }

  double 
  gettime(void){
    struct timeval ttime;
    gettimeofday( &ttime , 0 );
    return ttime.tv_sec + ttime.tv_usec * 0.000001;
  }

  
  void log(std::string s, INT x){
    std::cerr << s << x << std::endl;
  }

  
  void log(std::string s, INT x, INT y){
    std::cerr << s << x << " " << y << std::endl;
  }
} // end namespace
