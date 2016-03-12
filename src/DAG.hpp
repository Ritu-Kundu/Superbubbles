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

/** Defines the class DAG.
 * It represents a subgraph (which inherits from the class Graph) and also prepares the graph for detection.
 */

#ifndef DAG_HPP
#define DAG_HPP

#include <stack>
#include "Graph.hpp"
#include "CandidateList.hpp"

#include "../include/sdsl/rmq_support.hpp"

namespace supbub {

    /** Class DAG
     * A DAG is a graph represented as follows:
     *   - A vertex is represented by its vertex-id(local-id). Therefore in this file, vertex v means vertex with id=v.
     *
     * This implementation is based on the paper "Linear-Time Superbubble Identification Algorithm for  Genome Assembly" by Brankovic et.al.
     *
     *
     * This class provides for the following:
     *  - Preparing the graph for detection of superbubbles
     *  - Assisting in detection of superbubbles by providing the following
     *    -- Candidates list
     *    -- ordD array: giving Topological order of vertices
     *    -- Functions to answer the following queries
     *     --- Previous Entrance of a given node
     *     --- Vertex at a given order
     *     --- Range maximum query on OutChild
     *     --- Range minimum query on OutParent
     *
     */

    class DAG : public Graph {

      public:

        /** list of candidates
         * - Candidate-list is doubly-linked list of candidates.
         * - A candidate has the following information:
         *   -- vertexId : int representing the vertex.
         *   -- isEntrance: true if its an entrance, false otherwise.
         *   -- pvsEntrance: pointer to the previous entrance candidate in the list wrt this candidate. To be used only for exit candidates.  **See comments for pvsEntrance array in Graph.hpp**
         *   -- next: pointer to the next candidate in the list.
         *   -- pvs: pointer to previous candidate in the list.
         */

        CandidateList candidates;

        /** array of topological order of vertices
         * ordD[x] = y => vertex with id=x has y as topological order
         */
        uint64_t *ordD;

        /** Constructor
         * @param n total number of vertices
         */
        DAG( uint64_t n );

        /** Destructor */
        ~DAG();

        /** Returns the local-id of the source(r) of the graph.
        *
        * It is the second-last vertex.
        *
        */
        VertexID_t getSourceId();

        /** Returns the local-id of the terminal/sink(r') of the graph.
        *
        * It is the last vertex.
        *
        */
        VertexID_t getTerminalId();


        /** Prepare the data-structors required for detecting superbubbles
         * Assumes that this DAG has only one source and one terminal vertices.
         *  - Following is accomplished while this DAG prepares itself for detection:
         *     -- Generating Candidate List
         *     -- Filling invOrd array
         *     -- Filling ordD array
         *     -- Filling pvsEntrance array
         *     -- Preparing OutParent and OutChild for rmq
         */
        void prepareForSupBub();

        /** Returns the pointer to previous entrance, in the candidate list, for the given vertex.
        * **See comments for pvsEntrance array in Graph.hpp**
         * @param v vertex whose previous entrance is to be found
         * @return pointer to previous entrance for v or nullptr if v is invalid
         */
        Candidate *previousEntrance( VertexID_t v );


        /** Returns the vertex having the given topological order.
         */
        VertexID_t vertexAtOrder( uint64_t o );

        /** Returns the maximum OutChild in the given range .
         */
        int64_t rangeMaxOutChild( uint64_t start, uint64_t end );

        /** Returns the minimum OutParent in the given range .
         */
        uint64_t rangeMinOutParent( uint64_t start, uint64_t end );


        //////////////////////// private ////////////////////////
      private:

        /** array of ids of vertices indexed by topological order
         * invOrd[x] = y => vertex y has x as topological order
         */
        VertexID_t *invOrd;

        /** array of outParent
         * OutParent[ordD[v]] = ordD[u1 ] such that
         *                       ordD[u1 ] is the minimum ∀ui → v, i.e.
         *                        order of furthest(in topo order) parent
         */

        uint64_t *outParent;

        /** array of outChild
         * OutChild[ordD[v]] = ordD[u1 ] such that
         *                       ordD[u1 ] is the maximum ∀ v → ui,i.e.
         *                        order of furthest(in topo order) child
         */

        uint64_t *outChild;


        /** array of pointer to previous entrance candidate, in the candidate list, for each vertex
         * pvsEntrance[x] = py => py is pointer to an entrance candidate representing vertex y(y is the vertex's local-id more precisely) such that
         *                    order of y <= order of x
         *                    and order of y is as large as possible.
         * if x is itself an entrance candidate, then pvsEntrance[x] = pointer to candidate corresponding to x
         * NOTE: It is different from pvsEntrance pointer stored in a candidate.
         *       For example, say vertex v is both an exit and an entrance candidate. And vertex u is the previous entrance candidate in the candidate list, then in pvsEntrance array pvsEntrance[v] = v. Also, v as an entrance candidate in the list will have nullptr stored as its pvsEntrance while v as an exit candidate in the list will have pointer to candidate u stored as its pvsEntrance.
         *       pvsEntrance pointer stored in candidate itself is used only for exit candidates.
         */
        Candidate **pvsEntrance;

        /** OutParent array prepared to answer rmq in constant time */
        sdsl::rmq_succinct_sct<> *rmqOutParent;

        /** OutChild array prepared to answer rmq in constant time */
        sdsl::rmq_succinct_sct<false> *rmqOutChild;

        /** Fills the invOrd array with vertices in topological order
         */
        void fillTopologicalOrder();

        /** Sorts the vertices in topological order recursively by using DFS.
         * @param currentVertex vertex under consideration.
         * @param visited array marking the visisted vertices.
         * @param ordStack stack storing the result.
         */
        void topologicalSort( VertexID_t currentVertex,
                              bool *visited,
                              std::stack<VertexID_t> &ordStack );


        /** Genertaes Candidate List and fills pvsEntrance array.
         * Checks each vertex v:
         *   - adds it in the candidate-list as an exit candidate if
         *       it has at least one parent with exactly one child(out-degree 1).
         *   - adds it in the candidate-list as an entrance candidate if
         *        it has at least one child with exactly one parent(in-degree 1).
         *   - adds the pointer(in candidate-list) to previous entrance
         *       node encountered so far in pvsEntrance[v]. If v is an
         *       entrance candidate, pvsEntrance[v] = v.
         *
         */
        void prepareCandListNPvsEntrance();

        /** Generates OutChild and OutParent and preapres them to answer rmq in constant time.
         * OutChild[x] = y implies y is the order of the furthest(topologically) child of the vertex having order x. Or
         * OutChild[ordD[v]] = ordD[u2] | ordD[u2] is the maximum among all children of v.
         * OutParent[x] = y implies y is the order of the furthest(topologically) parent of the vertex having order x. Or
         * OutParent[ordD[v]] = ordD[u2] | ordD[u2] is the minimum among all parents of v.
         *
         */
        void prepareOutParNOutChildRMQ();


    };

} // end namespace
#endif
