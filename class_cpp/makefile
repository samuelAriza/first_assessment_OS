CXX = g++
CXXFLAGS = -Wall -Wextra -Iinclude -O2 -g
# Excluir single.cpp de los objetos comunes
SRC_ALL_CPP = $(wildcard src/*.cpp)
SRC_CPP = $(filter-out src/single.cpp, $(SRC_ALL_CPP))
SRC = $(SRC_CPP) ../struct_c/src/benchmark.c
OBJ = $(SRC:.cpp=.o)
OBJ := $(OBJ:.c=.o)  # también soporta .c → .o
TARGET = main
HARNESS = single

all: $(TARGET)

$(TARGET): $(OBJ) main.o
	$(CXX) $(OBJ) main.o -o $(TARGET)

main.o: main.cpp
	$(CXX) $(CXXFLAGS) -c main.cpp -o main.o

$(HARNESS): $(OBJ) src/single.o
	$(CXX) $(OBJ) src/single.o -o $(HARNESS)

clean:
	rm -f $(OBJ) main.o src/single.o $(TARGET) $(HARNESS)
