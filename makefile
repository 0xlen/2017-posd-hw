NAME = hw7
INC_DIR = include
objects := $(patsubst %.cpp,%.o,$(wildcard *.cpp))
VPATH = include/
REUIRED_OBJ = number.o variable.o struct.o term.o atom.o list.o node.o main.o iterator.o

all: $(objects)
ifeq ($(OS), Windows_NT)
	g++ -std=gnu++0x -o $(NAME) $(REUIRED_OBJ) -lgtest
else
	g++ -std=c++11 -o $(NAME) $(REUIRED_OBJ) -lgtest -lpthread
endif

%.o: %.cpp
ifeq ($(OS), Windows_NT)
	g++ -std=gnu++0x -c $< -I $(INC_DIR)
else
	g++ -std=c++11 -c $< -I $(INC_DIR)
endif

main.o: main.cpp term.o struct.o list.o
ifeq ($(OS), Windows_NT)
	g++ -std=gnu++0x -c main.cpp -I $(INC_DIR)
else
	g++ -std=c++11 -c main.cpp -I $(INC_DIR)
endif

clean:
ifeq (${OS}, Windows_NT)
	del *.o *.exe
	del $(NAME)
else
	rm -f *.o exp $(NAME)
endif
