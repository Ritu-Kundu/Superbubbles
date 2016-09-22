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

/** Implements class Graph
 */
#include "Graph.hpp"

namespace supbub {

  Graph::Graph(int64_t n) {
    _numVertices = n;
    _numEdges = 0;
    _adjList = new int64_t_LIST[n];
    std::fill_n(_adjList, _numVertices, int64_t_LIST{}); // set to empty list

   _parentList = new int64_t_LIST[_numVertices];
   std::fill_n(_parentList, _numVertices, int64_t_LIST{}); // set to empty list


    _inDegree = new int64_t[_numVertices];
    std::fill_n(_inDegree, _numVertices, 0); // set to 0

    _outDegree = new int64_t[_numVertices];
    std::fill_n(_outDegree, _numVertices, 0); // set to 0

   }

  Graph::~Graph() {
    delete[] _adjList;
    delete[] _parentList;
    delete[] _inDegree;
    delete[] _outDegree;
  }

  int64_t 
  Graph::numVertices(){
    return _numVertices;
  }

  int64_t 
  Graph::numEdges(){
    return _numEdges;
  }


  int64_t_LIST&
  Graph::getChildren(int64_t v){
    return  _adjList[v];
  }


  int64_t_LIST&
  Graph::getParents(int64_t v){
    return _parentList[v];
  }

  int64_t
  Graph::getInDegree(int64_t v){
    if (v < _numVertices && v >= 0) {
      return _inDegree[v];
    } else {
      log("Invalid v : ", v);
      return -1;
    }
  }

  int64_t
  Graph::getOutDegree(int64_t v){
    if (v < _numVertices  && v >= 0) {
      return _outDegree[v];
    } else {
      log("Invalid v : ", v);
      return -1;
    }
  }


  void 
  Graph::addEdge(int64_t u, int64_t v){
    if (u > _numVertices || v > _numVertices || u < 0 || v < 0) {
      log("Invalid u or v : ", u, v);
    }
    _adjList[u].push_back(v);
    _numEdges++;
    _inDegree[v]++;
    _outDegree[u]++;
    _parentList[v].push_back(u);
  }



  // In accordance with the explanation found on http://www.geeksforgeeks.org/tarjan-algorithm-find-strongly-connected-components/ and wikipedia
  /* Complexity: O(E + V)
     Tarjan's algorithm for finding strongly connected
     components.
     *disc[i] = Discovery time of node i. (Initialize to 0)
     *low[i] = Lowest discovery time reachable from node
     i.
     *scc[i] = Subgraph-id corresponding to the Strongly connected component of node i. (Doesn't
     need to be initialized)
     *st = Stack used by the algorithm (Initialize to an empty
     stack)
     *stacked[i] = True if i was pushed into s. (Initialize to
     false)
     *tick = Clock used for discovery times (Initialize to 0)
     *currentScc = ID of the current non-singleton scc being discovered
     (Initialize to 0)
  */
  int64_t 
  Graph::fillSCC(int64_t* scc) {
    int64_t* disc = new int64_t[_numVertices];
    int64_t* low = new int64_t[_numVertices];
    bool* stacked = new bool[_numVertices];
    std::stack<int64_t> *st = new std::stack<int64_t>();
 
    // Initialize disc, low and stacked arrays
    std::fill_n(disc, _numVertices, 0); // set to 0
    std::fill_n(low, _numVertices, 0); // set to 0
    std::fill_n(stacked, _numVertices, false); // set to 0

    // Set value of initial tick (clock), SCC Id 
    int64_t tick = 0;
    int64_t currentScc = 1; // 0 is reserved for singeton SCCs

    // Call the recursive helper function to find strongly
    // connected components in DFS tree with vertex 'i'
    for (int64_t i = 0; i < _numVertices; ++i) {
      if (disc[i] == 0) {
	findScc(i, disc, low, st, stacked, tick, currentScc, scc);
      }
    }

    // clean up
    delete[] disc;
    delete[] low;
    delete[] stacked;
    delete st;

    return currentScc;
  }

  void 
  Graph::printGraph(){
    int64_t_LIST_ITERATOR i;
    for(int64_t v=0; v <_numVertices; ++v){
      std::cout << std::endl << v << "-> ";
      for (i = _adjList[v].begin(); i != _adjList[v].end(); ++i) {
	std::cout << *i << " ";
      }
    }
  }
  
  //////////////////////// private ////////////////////////


  //TODO this may require an int64_t as the final pointer.
  // it seems to be causing compiler errors
  void 
  Graph::findScc(int64_t u, int64_t* disc, int64_t* low, std::stack<int64_t> *st,
		 bool* stacked, int64_t& tick, int64_t& currentScc, int64_t* scc) {
 
    // Initialize discovery time and low value
    disc[u] = low[u] = ++tick;
    st->push(u);
    stacked[u] = true;
 
    // Go through all vertices adjacent to this
    int64_t_LIST_ITERATOR i;
    for (i = _adjList[u].begin(); i != _adjList[u].end(); ++i) {
      int64_t v = *i;  // v is current adjacent of 'u'
      // If v is not visited yet, then recur for it
      if (disc[v] == 0) {
	findScc(v, disc, low, st, stacked, tick, currentScc, scc);
	// Check if the subtree rooted with 'v' has a
	// connection to one of the ancestors of 'u'
	// Case 1 : Tree Edge
	low[u]  = std::min(low[u], low[v]);
      }
 
      // Update low value of 'u' only if 'v' is still in stack
      // (i.e. it's a back edge, not cross edge).
      // Case 2: Back edge
      else if (stacked[v]) {
	low[u]  = std::min(low[u], disc[v]);
      }
    }
 
    // root vertex found, pop the stack and print an SCC
    int64_t sizeOfSCC = 0;
    if (low[u] == disc[u]) {
      int64_t w;
       do {
	w = st->top();
	stacked[w] = false;
	scc[w] = currentScc;
	st->pop();
	sizeOfSCC++;
      } while (w != u);
       
       if (sizeOfSCC == 1) { // A singleton scc
	 scc[w] = 0;	 
       }
       else { // Non-singleton scc
	 currentScc++;
       }
	
    }
  }


}// end namespace
 
