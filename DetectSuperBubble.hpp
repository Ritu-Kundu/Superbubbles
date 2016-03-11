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

/** Defines the class DetectSuperBubble.
 * It defines the functions to detect superbubbles in a general directed gaph.
 */

#ifndef DETECT_SUPERBUBBLE_HPP
#define DETECT_SUPERBUBBLE_HPP


#include "Graph.hpp"
#include "Subgraph.hpp"
#include "DAG.hpp"
#include "CandidateList.hpp"

namespace supbub{

  /** Class DetectSuperBubble
   *
   * It defines the functions to implement the following:
   *  - 1.Partitioning a general graph(H) into subgraphs (Gs). 
   *  - 2.Converting a cyclic subgraph(G) into acyclic(G').
   *  - 3.Detecting superbubbles in a single-source and single-sink DAG.
   *  - 4.Filtering out 'unreal' superbubbles. (Conversion to acyclic requires duplication of parts of the subgraph which may result into some superbubbles('unreal') detetected that occur in parts which do not belong to the original subgraph G.)
   * Steps 1, 2 and 4 are described in the paper(paper-1) "An O(m log m) -time Algorithm For Detecting Superbubbles" by Sung et al.
   * Step 3 is implemented as described in the paper 
(paper-2) "Linear-Time Superbubble Identification Algorithm for  Genome Assembly" by Brankovic et.al.
   *
   * This class provides for the following:
   *  - Finding superbubbles in a generaal directed graph.
   */

  class DetectSuperBubble {

  public:

    /** struct for a superbubble */
    struct SuperBubble{
      VERTEXID entrance; // id of entrance vertex
      VERTEXID exit; // id of exit vertex
    };

    /** type for list of superbubbles */
    typedef std::list<SuperBubble> SUPERBUBBLE_LIST;

    /** Finds superbubbles in the given graph.
     *
     * See paper-1 to understand its functioning.
     *
     * @param g reference to the graph in which superbubbles are to be found.
     * @param superBubblesList reference to list of superbubbles in which result is to be returned.
     */
    void find(Graph& g, SUPERBUBBLE_LIST& superBubblesList);

    //////////////////////// private ////////////////////////
  private:

    /** Finds superbubbles in the given graph.
     *
     * See paper-2 to understand its functioning. Only variation is from the paper is the format in which superbubbles are being reported. It does not return a list of struct superbubbles but superbubbles are reported as an array superBubblesArray. (It was necessary for filtering out 'unreal' superbubbles later.)
     *
     * Each vertex can be beginning of at most one superbubble:
     *   superBubblesArray[x] = y =><x, y> is a superbubble.
     *   superBubblesArray[x] = -1 => No superbubble starts at x.
     *
     * After the graph is preprocessed, SuperBubble processes the candidates-list of the graph in decreasing topological order (backwards).
     *
     * @param dag pointer to the DAG in which superbubbles are to be found.
     * @param superBubblesArray pointer to the array of superbubbles in which result is to be returned.
     */
    void 
    superBubble(DAG* dag, VERTEXID* superBubblesArray);
    
    /** Reports the superbubbles ending at the given exit candidate along with the nested superbubbles between the given entrance and exit candidates.
     *
     * See paper-2 to understand its functioning. Helper of superBubble.
     *
     * Checks the possible entrance candidates between start and exit starting with the nearest previous entrance candidate (to exit).
     * It is called for each exit candidate in a reverse order(of candidate list) either by algorithm SuperBubble or through a recursive call to identify a nested superbubble.
     * @param dag pointer to the DAG in which superbubbles are to be found.
     * @param mark pointer to the array marking the entrance candidates which have already been checked prior to the current exit position being considered. It allows to avoid checking the same path of entrance candidates repeatedly.
     * @param start pointer to start candidate.
     * @param exit pointer to exit candidate. 
     * @param superBubblesArray pointer to the array of superbubbles in which result is to be returned.
     */
     void 
     reportSuperBubble(DAG* dag, int64_t* mark, Candidate* start, Candidate* exit, VERTEXID* superBubblesArray);

    /** Validates the superbubbles starting and ending at the vertices corresponding to the given entrance and exit candidates.If not returns the alternative entrance candidate.
     *
     * See paper-2 to understand its functioning. Helper of reportSuperBubble.
     *
     * @param dag pointer to the DAG in which superbubbles are to be found.
     * @param start pointer to start candidate.
     * @param exit pointer to exit candidate. 
     * @return  startCand if vertices corresponding to startCand and endCands(say s and t) for a valid superbubble <s, t>.
     *          pointer to an alternative entrance candidate if startCand itself is not an entrance for a valid superbubble, whose vertex can form a superbubble ending at the vertex of endCand.
     *          nullptr if its invalid exit candidate
     */ 
     Candidate*
      validateSuperBubble(DAG* dag, Candidate* startCand, Candidate* endCand);

  };

} // end namespace
#endif
