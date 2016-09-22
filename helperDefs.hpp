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

#ifndef HELPER_DEFS
#define HELPER_DEFS

#include <sys/time.h>
#include <getopt.h>


#include "globalDefs.hpp"

namespace supbub{
struct InputFlags{
  char* input_filename;
  char* output_filename;

};

void usage (void);
int decodeFlags(int argc, char* argv [], struct InputFlags* flags);
double gettime(void);

void log(std::string s, int64_t x);

void log(std::string s, int64_t x, int64_t y);

} // end namespace

#endif
