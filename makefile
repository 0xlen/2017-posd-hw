NAME = hw2
INC_DIR = include

all: ${NAME}

${NAME}: mainTerm.o atom.o number.o variable.o

ifeq (${OS}, Windows_NT)
	g++ -o ${NAME} mainTerm.o atom.o number.o variable.o -lgtest
else
	g++ -o ${NAME} mainTerm.o atom.o number.o variable.o -lgtest -lpthread
endif

number.o: $(INC_DIR)/number.h number.cpp
	g++ -std=gnu++0x -c number.cpp

atom.o: $(INC_DIR)/atom.h atom.cpp
	g++ -std=gnu++0x -c atom.cpp

mainTerm.o: $(INC_DIR)/utTerm.h mainTerm.cpp
	g++ -std=gnu++0x -c mainTerm.cpp

variable.o: $(INC_DIR)/variable.h variable.cpp
	g++ -std=gnu++0x -c variable.cpp


clean:
ifeq (${OS}, Windows_NT)
	del *.o *.exe
else
	rm -f *.o exp
endif
