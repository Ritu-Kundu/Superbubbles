SUPBUB : SuperBubbles
=====================================
Vertices are represented by vertex-ids which are integers. : A wrapper can be written to handle named vertices later.


The code has the following modules :

- supbub : module containing main() method.
 + It is organised as follows:
  * supbub.cpp : 	contains the main() function.
 

- DetectSuperBubble : module containing the functions to detect superbubbles in a general directed gaph.
 + It processes the graph(H) by 
  * partitioning it into subgraphs(Gi)
  * converting cyclic(G) into acyclic(G') subgraph (DAG)
  * detecting superbubbles in the single-source and single-sink DAG
  * filtering out 'unreal' superbubbles. (Conversion to acyclic requires duplication of parts of the subgraph which may result into some superbubbles('unreal') being detetected that occur in the parts which do not belong to the original subgraph G.)

 + Steps 1, 2 and 4 are performed as described in the paper (paper-1) "An O(m log m) -time Algorithm For Detecting Superbubbles" by Sung et al.

 + Step 3 is implemented as described in the paper 
(paper-2) "Linear-Time Superbubble Identification Algorithm for  Genome Assembly" by Brankovic et.al. 

 + Other than the main method find(), it provides the following function used in the algorithm to detect superbubble in DAG (paper-2):
  * superBubble
  * reportSuperBubble
  * validateSuperBubbble
 + It is organised as follows:
  * DetectSuperBubble.cpp : 	contains the functions.
  * DetectSuperBubble.hpp : 	contains the declaration of functions and macros.

- Graph : module containing a Graph class.
 + It represents a graph as follows:
  * A vertex is represented by its vertex-id which is an int.
  * Edges between vertices are represented using ajacency list.

 + This class provides functions for the following:
  * Adding edges between vertices.
  * Printing the graph as adjacency list. 
  * Support to query the number of vertices, edges of the graph; children and parents of a vertex in the graph.
  * Support to partition the graph into set of subgraphs 
   -- This set comprises of the following subgraphs:
    --- one corresponding to each of the non-singleton Strongly Connected Component(scc)
    --- one which includes every singleton scc(vertex).
		
 + It is organised as follows:
  * Graph.cpp : 	implements the class.
  * Graph.hpp : 	defines the class.

- Subgraph : module containing a subgraph class which is a special type of Graph (hence inherits from Graph class).
 + A vertex in a subgraph is given a new vertex-id called 'local-id'. Its original id in the graph(H) from which this subgraph is obtained is called 'global-id'.

 + This class maintains the global-id of each of its vertices by maintaining an array. It is the responsibility of the original graph(H) to set the global-ids of the vertices in this subgraph.

 + This class provides for obtaining the underlying Directed Acyclic Graph(DAG), G', using the algorithm described in the paper "An O(m log m) -time Algorithm For Detecting Superbubbles" by Sung et al. This class is reponsible for creating and destroying its DAG.
  * For obtaining a DAG from a subgraph, method requires to create two vertices(u' and u'') for each vertex(u) in the subgraph except for source(r) and terminal/sink(r'). A source and a terminal are also added to this DAG. Then edges re added to DAG depending on some conditions (see the paper).
    -- Let offset is equal to the number of vertices(except r and r') in the subgraph.
   	   --- Thus, in a DAG of the subgpah, number of vertices = 2 * offset + 2
   	   --- This class approaches this 'duplication' of vertices by considering u and u' have same local-ids in the subgraph and its DAG while u'' has an id(called duplicate-local-id)) equal to (id of u + offset). To summarise,
			Id of u'(in G') = Id of u(in G)
			Id of u''(in G') = Id of u(in G) + offset
       --- Just like in G, G' also has source and terminal/sink vertices having ids equal to the second-last and last indices of the vertices respectively.
  
 + It also assists in filtering-out 'unreal' superbubbles found in its DAG by providing the following:
   * Answering the following queries:
    -- Id of u'' for a vertex u' in G'.
    -- Id of u' for some dplicate vertex u'' in G'.
    -- Does some given id of G' correspond to a duplicate u''?
    -- Offset of this subgraph. (as id of every u' is in the range[0, offset))
   *  - It also maintains the dicovery and finishing times of the vertices in its DFS traversal to answer queries of the form: Is vertex x an ancesstor of vertex y?

 + In short, this class provides for the following:
  * Setting global-id of a vertex.
  * Quering the global-id of a vertex. 
  * Generating underlying DAG G:
  * Assisting in reporting the 'real' superbubbles by providing functions to query the follwing:
    -- Id of u'' for a vertex u' in G'.
    -- Id of u' for some dplicate vertex u'' in G'.
    -- Does some given id of G' correspond to a duplicate u''?
    -- Is a vertex x an ancesstor of a vertex y? 
    -- Offset of this subgraph. (as id of every u' is in the range[0, offset))

 + It is organised as follows:
  * Subgraph.cpp : 	implements the class.
  * Subgraph.hpp : 	defines the class.


- DAG : module containing a DAG class which is a special type of Graph (hence inherits from Graph class).
 + It represents a single-source and single-sink DAG.
  - Source and terminal have ids corresponding to second-last and last integer in the range assigned for the vertices, i.e. \[0, size of the DAG\]
 + The implementation in this module is based on the paper "Linear-Time Superbubble Identification Algorithm for  Genome Assembly" by Brankovic et.al.

 + It prepares the graph for detection, by doing the following:
  * Topological sorting.
  * Building Candidate's list.
  * Calculating ordD array.
  * Calculating PreviousEntrance array.
  * Calculating OutParent and OutChild arrays and preparing them for constant time RMQ.

 + And using above it assists in detection of superbubbles by providing the following:
  * Candidates list
  * ordD array:  giving Topological order of vertices.
  * Functions to answer the following queries: 
   * Sorce and Terrminal/Sink ids.
   * Previous Entrance of a given node.
   * Vertex at a given order.
   * Range maximum query on OutChild.
   * Range minimum query on OutParent.
		
 + It is organised as follows:
 * DAG.cpp : 	implements the class.
 * DAG.hpp : 	defines the class.
 

- CandidateList : module containing a CandidateList class.
 + It represents a CandidateList which is a doubly-linked list.

 + It provides the support of the following functions required by the algorithm:
  * Inserting in the list (at the tail).
  * Deleting the candidate at the tail.
  * Checking if the list is empty.
  * Returning a pointer to the candidate at the head of the list.
  * Returning a pointer to the candidate at the tail of the list.
		
 + It is organised as follows:
 * CandidateList.cpp : 	implements the class.
 * CandidateList.hpp : 	defines the class.

 + This class was needed to be used instead of 'list container' provided in C++ because of following reasons:
  * The main reason is direct access (so that it is constant time) to the elements of the list using a pointer was required (for previousEntrance as well as next candidate).
    	List container gives a contant time access only to the head and tail elements. Also, it doesn't return the pointer to element.
	It only returns an iterator to either of the head or tail using front() and back() methods.
	A work-around would have been using iterators (instead of pointers) by making the list return the iterator of the newly added element using the back() method. But it would ve been an over-kill. 
  * Only a small fraction of the functionality provided by the list container was needed. So, it only made more sense to write a separate class providing that functionality which also enables the use of pointers.


- helper : module containing utility functions.
 + It provides the following funtions:
  * a function to parse the input flags.
  * A function to measure time.

 + It is organised as follows:
  * helper.cpp : 	contains the functions.
  * helperDefs.hpp : 	contains the declaration of functions and  macros.


- globalDefs: contains the definition and declaration used by each of the other modules.
 + It provides the following typedef:
  * INT is set either to 64 bits or to 32 bits integer depending on the makefile used.


NOTE: libsdsl folder cotains the library used for rmq.

