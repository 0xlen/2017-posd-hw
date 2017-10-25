NAME = hw3
INC_DIR = include
objects := $(patsubst %.cpp,%.o,$(wildcard *.cpp))
VPATH = include/

all: $(objects)
ifeq ($(OS), Windows_NT)
	g++ -std=c++11 -o $(NAME) $^ -lgtest
else
	g++ -std=c++11 -o $(NAME) $^ -lgtest -lpthread
endif

%.o: %.cpp
	g++ -std=c++11 -c $<

clean:
ifeq (${OS}, Windows_NT)
	del *.o *.exe
	del $(NAME)
else
	rm -f *.o exp $(NAME)
endif
