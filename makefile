NAME = hw3
INC_DIR = include
HEADERS = include/atom.h include/variable.h include/number.h include/term.h include/utVariable.h include/utStruct.h include/struct.h

all: ${NAME}

${NAME}: main.o

ifeq (${OS}, Windows_NT)
	g++ -o ${NAME} main.o -lgtest
else
	g++ -o ${NAME} main.o -lgtest -lpthread
endif

main.o: main.cpp $(HEADERS)
	g++ -std=gnu++0x -c main.cpp

clean:
ifeq (${OS}, Windows_NT)
	del *.o *.exe
else
	rm -f *.o exp
endif
