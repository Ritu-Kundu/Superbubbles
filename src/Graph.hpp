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

#include <stack>
#include <list>
#include "helperDefs.hpp"

namespace supbub {

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

    /** type definition for vertex */
    typedef int64_t VertexID_t;


    /** type definition for list of ids of vertices */
    typedef std::list<VertexID_t> VertexID_List_t;


    /** type definition for iterator of list of vertices */
    typedef VertexID_List_t::iterator VertexID_List_Iterator_t;


    class Graph {
      public:
        /** Constructor
         * @param n total number of vertices
         */
        Graph( uint64_t n );

        /** Destructor */
        virtual ~Graph();

        /** Gives the number of vertices of graph. */
        uint64_t numVertices();

        /** Gives the number of vertices of graph. */
        uint64_t numEdges();

        /** Returns list of children of the vertex.
         * Assumes v is valid.
         * @param v given vertex-id.
         * @return reference to list of ids of child vertices.
         */
        VertexID_List_t &getChildren( VertexID_t v );

        /** Returns list of parents of the vertex.
         * Assumes v is valid.
         * @param v given vertex-id.
         * @return reference to list of ids of parent vertices
         *
         */
        VertexID_List_t &getParents( VertexID_t v );

        /** Returns indegree of the vertex with given vertex-id (if v exists, -1 otherwise).
         */
        uint64_t getInDegree( VertexID_t v );

        /** Returns outdegree of the vertex with given vertex-id (if v exists, -1 otherwise).
         */
        uint64_t getOutDegree( VertexID_t v );


        /** Adds an edge
         * @param u id of source vertex of edge
         * @param v id of terminal vertex of edge
         */
        void addEdge( VertexID_t u, VertexID_t v );

        /** Fills the given array with ids of the subgraphs(coresponding to 'scc') which corresponding vertex belongs to.
         *
         * Each singleton vetex is added to the subgraph corresponding to id 0.
         * Each non-singleton scc corresponds to a subgraph (with id starting from 1).
         * Uses Tajan's algorithm to find scc.
         * Assumes size of given array is at least equal to number of vertices in the graph.
         * @param scc Pointer to the array to be filled in with subgraph-id of each vertex.
         * @return number of subgraphs(one corresponding to all vertices in singleton sccs and rest corresponding to each of the non-singleton scc) .
         */
        uint64_t fillSCC( uint64_t *scc );

        /* Prints the graph in the form of adjacency list
         */
        void printGraph();


        //////////////////////// protected ////////////////////////
      protected:
        /** total number of vertices in the graph */
        uint64_t _numVertices;

        /** total number of edges in the graph */
        uint64_t _numEdges;

        /** adjacency list
         *  it is the pointer to an array where an element at index say 'u' is a pointer to a list of ids 'v' of all vertices such that there is an edge from the vertex with id u to the vertex with id v.
         */
        VertexID_List_t *_adjList;

        /** parent list
         *  it is the pointer to an array where an element at index say 'u' is a pointer to a list of ids 'v' of all vertices such that there is an edge from the vertex with id v to the vertex with id u.
         */
        VertexID_List_t *_parentList;

        /** array of in-degree of each vertex
         *  it is the pointer to an array where an element at index say 'u' contains n where n is in-degree of the vertex width id  u.
         */
        uint64_t *_inDegree;

        /** array of out-degree of each vertex
         *  it is the pointer to an array where an element at index say 'u' contains n where n is out-degree of the vertex width id u.
         */
        uint64_t *_outDegree;

        //////////////////////// private ////////////////////////
      private:
        /** Finds out scc(/subgraph) of given vertex recursively by using DFS.
         * @param u id of vertex under consideration.
         * @param disc Pointer to the array marking the discovery time of each vertex. (Initialize to 0).
         * @param low  Pointer to the array marking the lowest discovery time reachable from each vertex.
         * @param st Pointer to the stack used by the algorithm (Initialize to an empty stack).
         * @param stacked  Pointer to the array marking if a vertex id is stacked or not
         *        - stacked[i]=true if i was pushed into st, else false. (Initialize to false).
         * @param tick Alias to the clock used for discovery times (Initialize to 0).
         * @param currentScc Alias to the id of the current non-singleton scc being discovered  (Initialize to 0)
      .
         * @param scc  Pointer to the array to be filled in with subgraph-id of each vertex.
         */

        void findScc( uint64_t u, uint64_t *disc, uint64_t *low, std::stack<uint64_t> *st, bool *stacked, uint64_t &tick, uint64_t &currentScc, uint64_t *scc );

    };

} // end namespace
#endif
