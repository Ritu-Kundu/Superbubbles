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

/** Defines the class Graph.
 * It represents a graph and also partitions the graph into suubgraphs.
 */

#ifndef GRAPH_HPP
#define GRAPH_HPP

#include "globalDefs.hpp"
#include "helperDefs.hpp"

namespace supbub{

  /** Class Graph
   * A graph is represented as follows:
   *   - A vertex is represented by its vertex-id which is an int.
   *   - Edges between vertices are represented using ajacency list.
   * A vertex and vertex-id are inter-changably used.
   * This class provides for the following:
   *  - Adding edges between vertices.
   *  - Printing the graph in adjacency-list format.
   *  - Support to query the number of vertices, edges; children and parents of a vertex.
   *  - Support to partition the graph into set of subgraphs 
   *    -- This set comprises of the following subgraphs:
   *       --- one corresponding to each of the non-singleton Strongly Connected Component(scc)
   *       --- one which includes every singleton scc(vertex).
   */

   /** type for vertex */
    typedef INT VERTEXID;

    
    /** type for list of ids of vertices */
    typedef std::list<VERTEXID> VERTEXID_LIST;

 
    /** type for iterator of list of vertices */
    typedef VERTEXID_LIST::iterator VERTEXID_LIST_ITERATOR;


  class Graph{

  public:

    /** Constructor
     * @param n total number of vertices
     */
    Graph(INT n); 

    /** Destructor */ 
    ~Graph();

    /** Gives the number of vertices of graph. */
    INT numVertices();

    /** Gives the number of vertices of graph. */
    INT numEdges();

    /** Returns list of children of the vertex.
     * Assumes v is valid.
     * @param v given vertex-id.
     * @return reference to list of ids of child vertices.
     */
    VERTEXID_LIST& getChildren(VERTEXID v);

    /** Returns list of parents of the vertex.
     * Assumes v is valid.
     * @param v given vertex-id.
     * @return reference to list of ids of parent vertices
     *         
     */
     VERTEXID_LIST& getParents(VERTEXID v);

    /** Returns indegree of the vertex with given vertex-id (if v exists, -1 otherwise).
     */
    INT getInDegree(VERTEXID v);

    /** Returns outdegree of the vertex with given vertex-id (if v exists, -1 otherwise).
     */
    INT getOutDegree(VERTEXID v);



    /** Adds an edge 
     * @param u id of source vertex of edge
     * @param v id of terminal vertex of edge
     */
    void addEdge(VERTEXID u, VERTEXID v);

    /** Fills the given array with ids of the subgraphs(coresponding to 'scc') which corresponding vertex belongs to.
     * 
     * Each singleton vetex is added to the subgraph corresponding to id 0.
     * Each non-singleton scc corresponds to a subgraph (with id starting from 1).
     * Uses Tajan's algorithm to find scc.
     * Assumes size of given array is at least equal to number of vertices in the graph.
     * @param scc Pointer to the array to be filled in with subgraph-id of each vertex.
     * @return number of subgraphs(one corresponding to all vertices in singleton sccs and rest corresponding to each of the non-singleton scc) .     
     */
     INT fillSCC(INT* scc);

    /* Prints the graph in the form of adjacency list 
     */
    void printGraph();


    //////////////////////// protected ////////////////////////
  protected:
    /** total number of vertices in the graph */
    INT _numVertices;

    /** total number of edges in the graph */
    INT _numEdges;

    /** adjacency list
     *  it is the pointer to an array where an element at index say 'u' is a pointer to a list of ids 'v' of all vertices such that there is an edge from the vertex with id u to the vertex with id v.
     */
    VERTEXID_LIST* _adjList;

    /** parent list
     *  it is the pointer to an array where an element at index say 'u' is a pointer to a list of ids 'v' of all vertices such that there is an edge from the vertex with id v to the vertex with id u.
     */
    VERTEXID_LIST* _parentList;

    /** array of indegree of each vertex
     *  it is the pointer to an array where an element at index say 'u' containes n where n is indegree of the vertexwith id  u.
     */
    INT* _inDegree;

    /** array of outdegree of each vertex
     *  it is the pointer to an array where an element at index say 'u' containes n where n is outdegree of the vertex with id u.
     */
    INT* _outDegree;
 
    //////////////////////// private ////////////////////////
  private:
    /** Finds out scc(/subgraph) of given vertex recursively by using DFS.
     * @param u id of vertex under consideration.
     * @param disc Pointer to the array marking the discovery time of each vertex. (Initialize to 0).
     * @param low  Pointer to the array marking the lowest discovery time reachable from each vertex.
     * @param st Pointer to the stack used by the algorithm (Initialize to an empty
     stack).
     * @param stacked  Pointer to the array marking if a vetex id is stacked or not
     *        - stacked[i]=true if i was pushed into st, else false. (Initialize to false).
     * @param tick Alias to the clock used for discovery times (Initialize to 0).
     * @param currentScc Alias to the id of the current non-singleton scc being discovered  (Initialize to 0)
  .
     * @param scc  Pointer to the array to be filled in with subgraph-id of each vertex.
     */

    void 
    findScc(INT u, INT* disc, INT* low, std::stack<int> *st,
	bool* stacked, INT& tick, INT& currentScc, INT* scc);
 
  };

} // end namespace
#endif
