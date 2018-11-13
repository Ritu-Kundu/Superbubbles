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

/** Defines the class Subgraph.
 * It represents a subgraph (which inherits from the class Graph), creates an underlying DAG, and also assists in filtering out 'unreal' superbubbles.
 */

#ifndef SUBGRAPH_HPP
#define SUBGRAPH_HPP

#include "Graph.hpp"
#include "DAG.hpp"

namespace supbub{

  /** Class Subgraph
   * A subgraph(G) is special graph obtained from a part of the original graph(H).
   * @see Graph.
   *
   * A vertex in a subgraph is given a new vertex-id called 'local-id'. Its original id in the graph(H) from which this subgraph is obtained is called 'global-id'.
   *
   * This class maintains the global-id of each of its vertices by maintaining an array. It is the responsibility of the original graph(H) to set the global-ids of the vertices in this subgraph.
   * 
   *
   * This class also provides for obtaining the underlying Directed Acyclic Graph(DAG), G', using the algorithm described in the paper "An O(m log m) -time Algorithm For Detecting Superbubbles" by Sung et al. This class is reponsible for creating and destroying its DAG.
   *  - For obtaining a DAG from a subgraph, method requires to create two vertices(u' and u'') for each vertex(u) in the subgraph except for source(r) and terminal/sink(r'). A source and a terminal are also added to this DAG. Then edges are added to DAG depending on some conditions (see the paper).
   *    -- Let offset is equal to the number of vertices(except r and r') in the subgraph.
   *       --- Thus, in a DAG of the subgpah, number of vertices = 2 * offset + 2
   *       --- This class approaches this 'duplication' of vertices by considering u and u' have same local-ids in the subgraph and its DAG while u'' has an id(called duplicate-local-id)) equal to (id of u + offset). To summarise,
   *           Id of u'(in G') = Id of u(in G)
   *           Id of u''(in G') = Id of u(in G) + offset
   *       --- Just like in G, G' also has source and terminal/sink vertices having ids equal to the second-last and last indices of the vertices respectively.
   *
   * It also assists in reporting 'real' superbubbles found in its DAG by providing the following:
   *  - Answering the following queries:
   *    -- Id of u'' for a vertex u' in G'.
   *    -- Does a given id of G' correspond to a duplicate u'' of some u'.
   *    -- Id of u' for some dplicate vertex u'' in G'.
   *    -- Offset of this subgraph. (as id of every u' is in the range[0, offset))
   *  - It also maintains the dicovery and finishing times of the vertices in its DFS traversal to answer queries of the form: Is vertex x an ancesstor of vertex y?
   *
   * To conclude, this class provides for the following:
   *  - Setting global-id of a vertex.
   *  - Quering the global-id of a vertex. 
   *  - Generating underlying DAG G:
   *  - Assisting in reporting the 'real' superbubbles by providing functions to query the follwing:
   *    -- Id of u'' for a vertex u' in G'.
   *    -- Id of u' for some dplicate vertex u'' in G'.
   *    -- Does some given id of G' correspond to a duplicate u''?
   *    -- Is a vertex x an ancesstor of a vertex y? 
   *    -- Offset of this subgraph. (as id of every u' is in the range[0, offset))
   *
   */

  class Subgraph : public Graph{

  public:
   
    /** Constructor
     * @param n total number of vertices
     */
    Subgraph(int64_t n); 

    /** Destructor */ 
    ~Subgraph();

    /** Returns the global-id for a given local-id.
     * @param v local vertex-id.
     * @return global vertex-id of v.
     *         or -1 if v is invalid
     */
    int64_t getGlobalId(int64_t v);

     /** Sets the global vertex-id of the given local vertex-id.
     * @param localId local-id of the vertex whose global-id is to be set.
     * @param globalId global-id to be set.
     */
    void setGlobalId(int64_t localId, int64_t globalId);

     /** Returns the local-id of the source(r) of the graph.
     *
     * It is the second-last vertex.
     *
     */

    int64_t getSourceId();

     /** Returns the local-id of the terminal/sink(r') of the graph.
     *
     * It is the last vertex.
     *
     */
    int64_t getTerminalId();

    /** Returns the duplicate-local-id of the vertex with the given local-id. 
     * @return duplicate-local-id of v or -1 if v is invalid
     */
    int64_t getDuplicateId(int64_t v);

    /** Returns the original-local-id of the vertex with the given duplicate-local-id. 
     * @return original-local-id of v or -1 if v is invalid
     */
    int64_t getOriginalId(int64_t v);

    /** Checks whether the given local-id corresponds to duplicate(u'') vertex in the resultant dag or not. 
     * @param v given local-id.
     * @return true if v is local-id corresponding to duplicate vertex(u'') in the resultant dag G'.
     *         false if v is local-id corresponding to original vertex(u') in the resultant dag G'.
     *         an invalid v also returns false. 
     */
    bool isDuplicateId(int64_t v);

    /** Checks whether the given vertex is an ancestor of the given other vertex in DFS tree of this subgraph.
     *
     * getDag() should have been called before making a call to this function.
     * 
     * @param anc given local-id of ancestor.
     * @param des given local-id of descendant.
     * @return true if anc is an ancestor of des (i.e. discovery and finishing time of des lies in the range corresponding to discovery and finishing times of anc).
     *         false if above condition isn't satisfied 
     *               or anc/des/both are invalid
     *               or getDAG() hasn't been called earlier than this function.
     * 
     */
    bool isAncestor(int64_t anc, int64_t des);

    /** Returns offset of this subgraph.
     */
    int64_t getOffset();

    /** Returns a pointer to the underlying DAG of this subgraph. 
     * Follows GraphToDAG method described in the paper.
     * Uses DFS to find back-edges required in the method.
     * At the same time fills the discovery and finishing time arrays of the vertices, required later while answering 'ancesstor queries'.
     * The random source-vertex selected(if any)[as required in the method] is that with the local-id 0. 
     */
    DAG* getDAG();

    //////////////////////// private ////////////////////////
  private:

    /** Pointer to the array mapping subgraph's(G) vertex id (local) to graph's(H) vertex id (global). */
    int64_t* _reverseMapId;

    /** Integer representing the offset between a vertex's local-id and its duplicate vetex's local-id in this subgraph's underlying DAG i.e. G'.
     *
     *  - 0 to offset-1 are ids of the original vertices(u') in the dag of this subgraph
     *  - offest to size(of dag)-2 are the ids of the duplicate vertices(u'').
     *    -- (size -2) because last and second-last correspond to sink and source resp.  
     * -- used for duplicating nodes while obtaining the DAG of this subgraph 
     */
    int64_t _offSet;

    DAG* _dag;

    /** Pointer to the array mapping subgraph's(G) vertices to their discovery time in DFS traversal. */
    int64_t* _discovery;

    /** Pointer to the array mapping subgraph's(G) vertices to their finishing time in DFS traversal. */
    int64_t* _finish;

    /** enum for vertex-color used in case of DFS to identify back-edges*/
    enum Color { WHITE, GRAY, BLACK };

    /** Adds edges to the underlying DAG along with filling discovery and finishing time of the vertices in DFS traversal. 
     * @param u root vertex.
     * @param tick clock for dicvery and finishing time.
     * @param color Pointer to an array marking colors of the vertices to keep track of unvisited(WHITE), visited but not finished(GRAY) and finished(BLACK) vertices.
     *
     */   
    void DFSVisit(int64_t u, int64_t& tick, Color* color);
  

 
  };

} // end namespace
#endif
