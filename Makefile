MF=Makefile
 
CXX=g++
 
CXXFLAGS= -msse3 -g -D_USE_32 -std=c++11 -fopenmp -O3 -fomit-frame-pointer -funroll-loops 
 
LFLAGS= -I. -L. -lsupbub -lsdsl

LIB=libsupbub.a
EXE=supbub
SRC=supbub.cpp Graph.cpp DetectSuperBubble.cpp Subgraph.cpp DAG.cpp CandidateList.cpp helper.cpp
HD=Graph.hpp DetectSuperBubble.hpp Subgraph.hpp DAG.hpp CandidateList.hpp helperDefs.hpp Makefile
OBJ=$(SRC:.cpp=.o)
 
# 
# No need to edit below this line 
# 
 
.SUFFIXES: 
.SUFFIXES: .cpp .o 

 
all: $(LIB) $(EXE)
 
DetectSuperBubble.o: DetectSuperBubble.cpp DetectSuperBubble.hpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

Subgraph.o: Subgraph.cpp Subgraph.hpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

DAG.o: DAG.cpp DAG.hpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

CandidateList.o: CandidateList.cpp CandidateList.hpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

helper.o: helper.cpp helperDefs.hpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

Graph.o: Graph.cpp Graph.hpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

supbub.o: supbub.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

$(LIB): DetectSuperBubble.o Subgraph.o DAG.o CandidateList.o helper.o Graph.o
	ar -rs $@ $^

$(EXE): $(LIB) $(OBJ)
	$(CXX) $(CXXFLAGS) -o $@ supbub.o $(LFLAGS)

$(OBJ): $(MF) $(HD)

clean:
	rm -f $(OBJ) $(EXE) *~
