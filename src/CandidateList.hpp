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

/** Defines the class CandidateList.
 */

#ifndef CANDIDATELIST_HPP
#define CANDIDATELIST_HPP

#include "globalDefs.hpp"

namespace supbub{

/** type for a candidate */
struct Candidate{
  INT vertexId; // int representing the vertex
  bool isEntrance;  // true if its an entrance, false otherwise

  /** pointer to previous entrance candidate in the list wrt this candidate if it's an exit candidate. For an entrance candidate, it is null.
   * To be used only for exit candidates. 
   * **See comments for pvsEntrance array in DAG.hpp** */
  Candidate* pvsEntrance;  

  Candidate* next;  // pointer to next node
  Candidate* pvs;  // pointer to previous node
};

  /** Class CandidateList
   * A CandidateList is doubly-linked list of candidates.
   * This class provides for the following:
   *  - Inserting in the list (at the tail).
   *  - Deleting the candidate at the tail.
   *  - Checking if the list is empty.
   *  - Returning a pointer to the candidate at the head of the list.
   *  - Returning a pointer to the candidate at the tail of the list.
   */

  class CandidateList{

  public:

    /** Constructor */
    CandidateList();

    /** Destructor */ 
    ~CandidateList();

    /** Adds a candidate at the tail.
     * @param ver vertexId of the candidate
     * @param isEntrance // true if its an entrance, false otherwise
     * @param pvsEntrance pointer to previous entrance candidate in the list wrt this candidate if it's an exit candidate. For an entrance candidate, it is null.
     */
    Candidate* insert(INT ver, bool isEntrance, Candidate* pvsEntrance); 

    /** Returns a pointer to the candidate at the tail of the list. */
    Candidate* tail();

    /** Returns a pointer to the candidate at the head of the list. */
    Candidate* front();

    /** Checks if the list is empty. */
    bool empty();

    /** Delets the element at the tail. */
    void delete_tail();

  private:

    /** pointer to the candidate at the head of the list */
    Candidate* _front;

   /** pointer to the candidate at the tail of the list */
    Candidate* _tail;

  };

} // end namespace
#endif
