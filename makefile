NAME = HW1
INC_DIR = include

all: ${NAME}

${NAME}: main.o Sort.o Shapes.o Media.o
ifeq (${OS}, Windows_NT)
	g++ -o ${NAME} main.o Shapes.o Media.o Sort.o -lgtest
else
	g++ -o ${NAME} main.o Shapes.o Media.o Sort.o -lgtest -lpthread
endif


main.o: main.cpp utSort.h
	g++ -std=gnu++0x -c main.cpp

Sort.o: $(INC_DIR)/Sort.h Sort.cpp
	g++ -std=gnu++0x -c Sort.cpp

Shapes.o: $(INC_DIR)/Shapes.h Shapes.cpp
	g++ -std=gnu++0x -c Shapes.cpp

Media.o: $(INC_DIR)/Media.h Media.cpp
	g++ -std=gnu++0x -c Media.cpp


clean:
ifeq (${OS}, Windows_NT)
	del *.o *.exe
else
	rm -f *.o exp
endif