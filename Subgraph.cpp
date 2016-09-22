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

/** Implements class Subraph
 */
#include "Subgraph.hpp"

namespace supbub{

  Subgraph::Subgraph(int64_t n):Graph(n) {
    //super();
    _reverseMapId = new int64_t[_numVertices];
    std::fill_n(_reverseMapId, _numVertices, -1); // set to -1
    _offSet = n-2;
    _dag = nullptr;
    _discovery = nullptr;
    _finish = nullptr;
    
  }

  Subgraph::~Subgraph() {
    delete[] _reverseMapId;
    if (_dag != nullptr) {
      delete _dag;
      delete[] _discovery;
      delete[] _finish;
    }
  }

  int64_t
  Subgraph::getGlobalId(int64_t v){
    if (v < _numVertices && v >=0 ) {
      return _reverseMapId[v];
    } else {
      log("Invalid v : ", v);
      return -1;
    }
  }

  void
  Subgraph::setGlobalId(int64_t localId, int64_t globalId){
    if (localId <_numVertices && localId >=0 ) { 
      _reverseMapId[localId] = globalId;
    } else {
      log("Invalid localId : ", localId);
    }
  }

  int64_t
  Subgraph::getSourceId(){
    return _numVertices-2; // second last vertex
  }

  int64_t
  Subgraph::getTerminalId(){
    return _numVertices-1; // last vertex
  }

  int64_t
  Subgraph::getDuplicateId(int64_t v){
    if (v < _numVertices && v >=0 ) {
      return v + _offSet;
    } else {
      log("Invalid v : ", v);
      return -1;
    }
  }

  int64_t
  Subgraph::getOriginalId(int64_t v){
    if (v < 2*_offSet && v >= _offSet ) {
      return v - _offSet;
    } else {
      log("Invalid v'' : ", v);
      return -1;
    }
  }

  bool
  Subgraph::isDuplicateId(int64_t v){
   if (v < _numVertices && v >=0 ) {
     return !(v < _offSet);
    } else {
      log("Invalid v : ", v);
      return false;
    }
  }

  bool
  Subgraph::isAncestor(int64_t anc, int64_t des){
    if (anc < _numVertices && anc >=0 && des < _numVertices && des > 0) {
      if (_dag != nullptr) {
	return (_discovery[des] > _discovery[anc] && _finish[des] < _finish[anc]);
      } else {
	log("DFS Traversal not made yet. Call getDAG() before making call to this function.", 0);
	return false;
      }
    } else {
      log("Invalid ancestor or descendent id : ", anc, des);
      return false;
    }
  }

  int64_t Subgraph::getOffset(){
    return _offSet;
  }


  DAG*
  Subgraph::getDAG(){
    _dag = new DAG(2*_offSet + 2);
    _discovery = new int64_t[_numVertices];
    _finish = new int64_t[_numVertices];
    int64_t_LIST_ITERATOR i;
    int64_t newSource = _dag->getSourceId();
    int64_t thisSource = getSourceId();
    int64_t newTerminal = _dag->getTerminalId();
    int64_t thisTerminal = getTerminalId();

    
    /* Add {(r, v' ) | (r, v) ∈ E(G)} */
    if (! _adjList[thisSource].empty()) {
      for (i = _adjList[thisSource].begin(); i != _adjList[thisSource].end(); ++i) {
	if (*i != thisTerminal) {
	  _dag->addEdge(newSource, *i); //  as v and v' have same local-id
	}
      }
    }

    /* Add {(v'' , r' ) | (v, r' ) ∈ E(G)} */
    if (! _parentList[thisTerminal].empty()) {
      for (i = _parentList[thisTerminal].begin(); i != _parentList[thisTerminal].end(); ++i) {
	if (*i != thisSource) {
	_dag->addEdge(getDuplicateId(*i), newTerminal);
	}
      }
    }

    /* Add {(u', v'), (u'', v'') |(u, v) ∈ E(G), (u, v) is not a back edge } and {(u', v'') | (u, v) ∈ E(G), (u, v) is a back edge} */
    int64_t source = thisSource;
    if (_outDegree[thisSource] == 0) { // no source r, select a random vertex to be source/root
      source = 0; // 0 is chosen
    }
    Subgraph::Color* color = new Subgraph::Color[_numVertices];
    std::fill_n( color, _numVertices, WHITE ); // set to false
    DFSVisit(source, 0, color);

    /* Adjust source and terminal vertices */
    int64_t lastDAGID = _dag->numVertices()-2;
    if (_outDegree[thisSource] == 0) { // G does not contain r
      for (int64_t u=0; u < lastDAGID; ++u) {
	if (_dag->getInDegree(u) == 0) { // for every u ∈ V (G ) such that u has no incoming edge in G'
	  _dag->addEdge(newSource, u);//create an edge (r, u)
	}
      }
    }
    if (_inDegree[thisTerminal] == 0) { // G does not contain r'
      for (int64_t u=0; u < lastDAGID; ++u) {
	if (_dag->getOutDegree(u) == 0) { // for every u ∈ V (G ) such that u has no outgoing edge in G'
	  _dag->addEdge(u, newTerminal);//create an edge (u, r')
	}
      }
    }
    //clean-up
    delete[] color;

    return _dag;
  }


  //////////////////////// private ////////////////////////


  void
  Subgraph::DFSVisit(int64_t u, int64_t tick, Subgraph::Color* color){
    color[u] = GRAY;
    _discovery[u] = ++tick;
    int64_t_LIST_ITERATOR i;
    int64_t thisSource = getSourceId();
    int64_t thisTERMINAL = getTerminalId();
    if (! _adjList[u].empty()) {
      for (i = _adjList[u].begin(); i != _adjList[u].end(); ++i) {	
	int64_t v = *i;
	if (color[v] == WHITE){ // u-v is tree-edge
	  if (v != thisTERMINAL && u!= thisTERMINAL && v!=thisSource && u!=thisSource) {
	    _dag->addEdge(u, v); // add u'-v'
	    _dag->addEdge(getDuplicateId(u), getDuplicateId(v)); // add u''-v''
	  }
	  DFSVisit(v, tick, color);
	}
	else if (color[v] == GRAY) { // u-v is back edge
	  if (v != thisTERMINAL && u!= thisTERMINAL && v!=thisSource && u!=thisSource) {
	    _dag->addEdge(u, getDuplicateId(v)); // add u'-v''
	  }
	}
	else{// forward or cross edge
	  if (v != thisTERMINAL && u!= thisTERMINAL && v!=thisSource && u!=thisSource) {
	    _dag->addEdge(u, v); // add u'-v'
	    _dag->addEdge(getDuplicateId(u), getDuplicateId(v)); // add u''-v''
	  }
	}
      }
    }    
    color[u] = BLACK;
    _finish[u] = ++tick;
  }


}// end namespace
 
