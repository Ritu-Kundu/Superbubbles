MF=Makefile
SDSL_DIR=./sdsl-lite
 
CC=g++
 
CFLAGS= -g -D_USE_32 -msse3 -fopenmp -O3 -fomit-frame-pointer -funroll-loops 
 
LFLAGS= -std=c++11 -O3 -DNDEBUG -I $(SDSL_DIR)/include/ -lsdsl ##-Wl,-rpath $(PWD)/sdsl-lite/lib -L $(SDSL_DIR)/lib/

LIB=libsupbub.a
EXE=supbub
SRC=supbub.cpp Graph.cpp DetectSuperBubble.cpp Subgraph.cpp DAG.cpp CandidateList.cpp helper.cpp
HD=globalDefs.hpp Graph.hpp DetectSuperBubble.hpp Subgraph.hpp DAG.hpp CandidateList.hpp helperDefs.hpp Makefile
OBJ=$(SRC:.cpp=.o)
 
# 
# No need to edit below this line 
# 
 
.SUFFIXES: 
.SUFFIXES: .cpp .o 

 
all: $(LIB) $(EXE)
 
.cpp.o: 
	$(CC) $(CFLAGS)-c $(LFLAGS) $< 

$(LIB): $(OBJ) 
	ar -rs $@ $(OBJ)

$(SDSL_DIR)/lib/libsdsl.a:
	+cd $(SDSL_DIR) && ./install.sh `pwd`

$(EXE): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $(OBJ) $(LFLAGS) 

$(OBJ): $(MF) $(HD)

clean:
	rm -f $(OBJ) $(EXE) *~
