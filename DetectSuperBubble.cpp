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
#include "DetectSuperBubble.hpp"

namespace supbub {

  void 
  DetectSuperBubble::find(Graph& g, SUPERBUBBLE_LIST& superBubblesList){
    int64_t numVertices = g.numVertices();

    /*******************************STAGE 1***************************************/

    /* Find scc (all singleton-vertices seen as scc with id zero, non-singleton starts from 1) */
    int64_t* scc = new int64_t[numVertices];
    int64_t numSubgraphs = g.fillSCC(scc);

    /* Preprocess before partitioning */
    std::vector<Subgraph*> subgraphs;
    int64_t* globalToLocalIdMap = new VERTEXID[numVertices]; // Keep track of local-ids given to vertices in each subgraph
    
    int64_t* sizeSubgraph = new int64_t[numSubgraphs]; // Keep track of size of each subgraph 
    std::fill_n(sizeSubgraph, numSubgraphs, 0); // set to 0
   
    // Calculate size of ssc/subgraphs, providing local-id to each vertex in that subgraph
    for(VERTEXID v=0; v < numVertices; ++v) {
      globalToLocalIdMap[v] = (sizeSubgraph[scc[v]])++;   
    }

    // Create new subgraphs of size just calculated (+ two extra vertices as r and r')
    for(int64_t sg=0; sg < numSubgraphs; ++sg) {
      subgraphs.push_back(new Subgraph(sizeSubgraph[sg] +2)); // two additional vetices for r(source) and r'(terminal/sink) resp.

    }

    /* Start PartitionGraph */
    VERTEXID_LIST_ITERATOR i;
    bool isOutOtherScc, isInOtherScc;
    for(VERTEXID v=0; v < numVertices; ++v) {
      Subgraph* sg = subgraphs[scc[v]];
      sg->setGlobalId(globalToLocalIdMap[v], v); // set reverse id map for this vertex
      VERTEXID_LIST& children = g.getChildren(v);
      if (! children.empty()) { // out-degree non-zero
	isOutOtherScc = false;
	for (i = children.begin(); i != children.end(); ++i) {
	  int64_t u = *i;
	  if (scc[v] == scc[u]){ // same scc
	    sg->addEdge(globalToLocalIdMap[v], globalToLocalIdMap[u]); // add edge v-u
	  }
	  else if (!isOutOtherScc) {  // if this is the first edge out-going to other scc
	    isOutOtherScc = true; // to avoid mutiple edges between same pair (v-r')
	    sg->addEdge(globalToLocalIdMap[v], sg->getTerminalId()); // edge v-r'
	  }
	}
      }
      else if (scc[v] == 0) { // out-degree zero and belongs to singleton subgraph
	sg->addEdge(globalToLocalIdMap[v], sg->getTerminalId());
      }

      // add edges r-v
      VERTEXID_LIST& parents = g.getParents(v);
      if (! parents.empty()) {
	for (i = parents.begin(); i != parents.end(); ++i) {
	  int64_t u = *i;
	  if (scc[v] != scc[u]){ // different scc
	    sg->addEdge(sg->getSourceId(), globalToLocalIdMap[v]); // add edge r-v
	    break;
	  }	  
	}
      }
      else if (scc[v] == 0) { // in-degree zero and belongs to singleton subgraph
	sg->addEdge(sg->getSourceId(), globalToLocalIdMap[v]);
      }
    }
    // Clean-up before prceeding to next stages 
    delete[] scc; 
    delete[] globalToLocalIdMap;
    delete[] sizeSubgraph;

    /*********************** STAGEs 2 and 3 (combined) ***************************/

    /* Obtain superbubble for acyclic */
    // Subgraph with id 0(corresponding to singletons) is already a Directed Acyclic Graph. Duplicate its edges into a DAG.
    Subgraph* sg0 = subgraphs[0];
    int64_t DAGSize = sg0->numVertices();
    DAG* dag0 = new DAG(DAGSize);

    for (VERTEXID v = 0; v < DAGSize; ++v) {
      VERTEXID_LIST& children = sg0->getChildren(v);
      if (! children.empty()) { // out-degree non-zero
	for (i = children.begin(); i != children.end(); ++i) {	
	  dag0->addEdge(v, *i); // add edge v-u	 
	}
      }
    }

    VERTEXID* superBubblesArray = new VERTEXID[DAGSize];
    std::fill_n(superBubblesArray,DAGSize, -1); // set to -1
    // find superbubles
    superBubble(dag0, superBubblesArray);

    // Filter out 'unreal' superbubbles
    VERTEXID lastPossibleS = DAGSize -2; // (last two vertices are dummu source and sink)
    VERTEXID dumyTerminal = dag0->getTerminalId();
    for (VERTEXID s=0; s < lastPossibleS; ++s) {
      VERTEXID t = superBubblesArray[s];
      if ( t!= -1 && t!=dumyTerminal) {
	superBubblesList.push_back(SuperBubble{sg0->getGlobalId(s), sg0->getGlobalId(t)});
      }
	
    }

    delete sg0;
    delete dag0;
    delete[] superBubblesArray;
    
    
    /* Detect superbubbles after changing cyclic G to acyclic G' */
    for(int64_t i=1; i < numSubgraphs; ++i) {
      Subgraph* sg = subgraphs[i];
      DAG* dag = sg->getDAG();

      // Array containing result: superBubblesArray[x] = y => <x,y> is a superbubble.
      // If x is not an entrance to any superbubble, superBubblesArray[x] = -1 
      superBubblesArray = new VERTEXID[dag->numVertices()];
      std::fill_n(superBubblesArray,dag->numVertices(), -1); // set to -1

      superBubble(dag,superBubblesArray);

      // Filter out 'unreal' superbubbles
      VERTEXID lastPossibleS = sg->getOffset();
      VERTEXID dumyTerminal = dag->getTerminalId();
      for (VERTEXID s=0; s < lastPossibleS; ++s) { // we will only consider u' and not u'' or r' or r''
	VERTEXID t = superBubblesArray[s];
	if ( t!= -1 && t!=dumyTerminal) { // s is entrance of possible 'real' superbubble

	  if (sg->isDuplicateId(t)) { // It corresponds to <s', t''>
	    VERTEXID realT = sg->getOriginalId(t);
	    if (sg->isAncestor(realT, s)) { // if t is ancesstor of s, <s, t> is superbubble
	      superBubblesList.push_back(SuperBubble{sg->getGlobalId(s), sg->getGlobalId(realT)});
 
	    }
	  }
	  else { // it corresponds to <s', t'>
	    VERTEXID s2 = sg->getDuplicateId(s);
	    VERTEXID t2 = sg->getDuplicateId(t);
	    if (superBubblesArray[s2] == t2) { // if <s'', t''> is also superbubble, then <s, t> is superbubble
	      superBubblesList.push_back(SuperBubble{sg->getGlobalId(s), sg->getGlobalId(t)});
	    }
	  }
	}
	
      }

      // clean-up
      delete sg;
      delete[] superBubblesArray;
    }    
  }

 //////////////////////// private //////////////////////// 

  void 
  DetectSuperBubble::superBubble(DAG* dag, VERTEXID* superBubblesArray){ 
    /* mark is used by reportSuperBubble() to keep track of the 
     * entrance candidates which have already been checked prior 
     * to the current exit position being considered. 
     * It allows to avoid checking the same path of entrance 
     * candidates repeatedly 
     */
    int64_t* mark = new int64_t[dag->numVertices()];
    std::fill_n(mark,dag->numVertices(), 0); // set to 0
    
    dag->prepareForSupBub();

    while (!dag->candidates.empty()) {
      if (dag->candidates.tail()->isEntrance) {
	dag->candidates.delete_tail();
      }
      else {
	reportSuperBubble(dag, mark, dag->candidates.front(), dag->candidates.tail(), superBubblesArray);
      }
    }
    delete[] mark;
  }
 

  void 
  DetectSuperBubble::reportSuperBubble(DAG* dag, int64_t* mark, Candidate* start, Candidate* exit, VERTEXID* superBubblesArray){
    // sanity check
    if (start == nullptr || exit == nullptr || dag->ordD[start->vertexId] >= dag->ordD[exit->vertexId]){ 
      dag->candidates.delete_tail();
      return; 
    }
    // Here previous entrance of exit candidate is used
    Candidate* s = exit->pvsEntrance;
    Candidate* valid = nullptr;
    while(dag->ordD[s->vertexId] >= dag->ordD[start->vertexId]){
      valid = validateSuperBubble(dag, s, exit);
      if (valid==s || valid->vertexId == mark[s->vertexId] || valid == nullptr){
	break;
      }
      mark[s->vertexId] = valid->vertexId;
      s = valid;
    }

    int64_t exitVer = exit->vertexId;
    dag->candidates.delete_tail(); 

    if (valid == s) {  // superbubble found
      // report superbubble
      superBubblesArray[s->vertexId] = exitVer;
      
      Candidate* nextCand = dag->candidates.tail();
      while (nextCand != s){ 
	if (! nextCand->isEntrance){  // candidate is an exit candidate
	  // check for nested superbubbles
	  reportSuperBubble(dag, mark, s->next, nextCand, superBubblesArray);
	}
	else {  // entrance candidate
	  dag->candidates.delete_tail(); 
	}
	nextCand = dag->candidates.tail();
      }
    }
  }

  Candidate*
  DetectSuperBubble::validateSuperBubble(DAG* dag, Candidate* startCand, 
					 Candidate* endCand){
    int64_t start = dag->ordD[startCand->vertexId];
    int64_t end = dag->ordD[endCand->vertexId];
    int64_t outChild = dag->rangeMaxOutChild(start, end-1);
    int64_t outParent = dag->rangeMinOutParent(start+1, end);
   
    if (outChild != end){
      log("returning null for : ", startCand->vertexId, endCand->vertexId);
      return nullptr;
    } 
    if (outParent == start) {
       return startCand;
    } 
    else {
      // Here previous entrance of vertex (general) is used
      return dag->previousEntrance(dag->vertexAtOrder(outParent));
    }
  }
}// end namespace
 
