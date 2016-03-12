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

/** Implements the class CandidateList
*/

#include <stdint.h>
#include "CandidateList.hpp"

namespace supbub {

    CandidateList::CandidateList() {
        _front = nullptr;
        _tail = nullptr;
    }

    CandidateList::~CandidateList() {
        while( !empty()) {
            delete_tail();
        }
    }

    Candidate *CandidateList::insert( uint64_t ver, bool isEntrance, Candidate *pvsEntrance ) {
        Candidate *newCand = new Candidate { ver, isEntrance, pvsEntrance, nullptr, _tail };

        // if it's not the first node, set tail to it
        if( _tail != nullptr ) {
            _tail->next = newCand;
            _tail = newCand;
        }
        else {  // if it's first node, set front
            _front = newCand;
            _tail = newCand;
        }
        return newCand;
    }

    Candidate *CandidateList::tail() {
        return _tail;
    }

    Candidate *CandidateList::front() {
        return _front;
    }

    bool CandidateList::empty() {
        return ( _front == nullptr && _tail == nullptr );
    }

    void CandidateList::delete_tail() {
        if( _tail != nullptr ) {
            if( _front == _tail ) {  // last element in the list
                delete _tail;
                _front = nullptr;
                _tail = nullptr;
            }
            else {
                Candidate *newTail = _tail->pvs;
                delete _tail;
                newTail->next = nullptr;
                _tail = newTail;
            }
        }
    }


}// end namespace
