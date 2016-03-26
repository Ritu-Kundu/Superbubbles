MF=Makefile 
CC= g++
CFLAGS= -g -msse3 -fopenmp -O3 -fomit-frame-pointer -funroll-loops 
LFLAGS= -std=c++11 -O3 -DNDEBUG -lsdsl
EXE= supbub
SRC= supbub.cpp Graph.cpp DetectSuperBubble.cpp Subgraph.cpp DAG.cpp CandidateList.cpp helper.cpp
HD=  globalDefs.hpp Graph.hpp DetectSuperBubble.hpp Subgraph.hpp DAG.hpp CandidateList.hpp helperDefs.hpp Makefile
 
# 
# No need to edit below this line 
# 
 
.SUFFIXES: 
.SUFFIXES: .cpp .o 
 
OBJ=    $(SRC:.cpp=.o) 
 
.cpp.o: 
	$(CC) $(CFLAGS)-c $(LFLAGS) $< 
 
lib: $(OBJ)
	ar rcu libsupbub.a *.o

all:    $(EXE) 
 
$(EXE): $(OBJ) 
	$(CC) $(CFLAGS) -o $@ $(OBJ) $(LFLAGS) 
 
$(OBJ): $(MF) $(HD) 
 
clean: 
	rm -f $(OBJ) $(EXE) *~

clean-all: 
	rm -f $(OBJ) $(EXE) *~
	rm -r libsdsl
	rm -r sdsl-lite
