CC = gcc
CFLAGS = -Wall -Wextra -Iinclude -O2 -g
# Excluir single.c de los objetos comunes
SRC_ALL = $(wildcard src/*.c)
SRC_COMMON = $(filter-out src/single.c, $(SRC_ALL))
OBJ_COMMON = $(SRC_COMMON:.c=.o)
TARGET = main
HARNESS = single

all: $(TARGET)

$(TARGET): $(OBJ_COMMON) main.o
	$(CC) $(OBJ_COMMON) main.o -o $(TARGET)

$(HARNESS): $(OBJ_COMMON) src/single.o
	$(CC) $(OBJ_COMMON) src/single.o -o $(HARNESS)

main.o: main.c
	$(CC) $(CFLAGS) -c main.c -o main.o

clean:
	rm -f $(OBJ_COMMON) main.o src/single.o $(TARGET) $(HARNESS)
