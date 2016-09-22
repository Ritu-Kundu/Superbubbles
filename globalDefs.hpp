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

/** Declaration used by each of the other modules
*/

#ifndef GLOBAL_DEFS
#define GLOBAL_DEFS

#include <cstdint>
#include <stdio.h>
#include <iterator>
#include <list>
#include <stack>
#include <string>
#include <iostream>


namespace supbub{
#define DEBUG
#ifdef _USE_64
  //typedef int64_t INT;
#endif

#ifdef _USE_32
  //typedef int32_t INT;
#endif

} // end namespace

#endif
