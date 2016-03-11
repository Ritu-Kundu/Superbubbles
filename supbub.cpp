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

/** Module containing main() method.
 */

#include <fstream>
#include <cstdlib>
#include <cstdint>
#include <stdio.h>
#include <iterator>
#include <list>
#include <stack>
#include <string>
#include <iostream>

#include "Graph.hpp"
#include "DetectSuperBubble.hpp"
#include "helperDefs.hpp"


using namespace supbub;
using namespace std;

int main(int argc, char **argv){
  
  /* Decode arguments */
  struct InputFlags flags;
  if(decodeFlags (argc, argv, &flags ) == 0){
    usage();
    return (1);
  }
  /* Read the input file in memory */
  std::ifstream infile(flags.input_filename);
  if(!infile.is_open()){
    fprintf(stderr, "Cannot open input file \n" );
    return 1;
  }
  // First line of the file contains number odf vertices
  int64_t numVertices;
  infile >> numVertices;
  Graph graph(numVertices);

  // File contains edges such that
  //  - new line as separator between edges
  //  - space/tab a separator between vertices of an edge
  int64_t u, v;
  while (infile >> u >> v) {
    // add egde in the graph
    graph.addEdge(u, v);
  }



  /* List for results */
  DetectSuperBubble::SUPERBUBBLE_LIST superBubblesList{};

  /* Find superbubbles */
  double start = gettime();
  DetectSuperBubble dsb;
  dsb.find(graph, superBubblesList); 
  double end = gettime();

 cerr << "Superbubs found" << endl;

  /* Write output */
  std::ofstream outfile(flags.output_filename);
  if(!outfile.is_open()){
    fprintf(stderr, "Cannot open output file \n" );
    return 1;
  }
  
  outfile <<  "Vertices: " << numVertices << "\n";
  outfile << "Edges: "<< graph.numEdges() << "\n";
  outfile << "Elapsed time for processing: " << (end - start)<< " secs.\n";
  outfile << "Number of superbubbles found: " << superBubblesList.size()<< ".\n";
  DetectSuperBubble::SUPERBUBBLE_LIST::iterator i;
  for (i = superBubblesList.begin(); i != superBubblesList.end(); ++i) {
    outfile << "<"<< (*i).entrance << "," << (*i).exit << ">\n";
  }
  // clean up
  delete[] flags.input_filename;
  delete[] flags.output_filename;
  
}


