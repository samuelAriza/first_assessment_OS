CC = gcc
CFLAGS = -Wall -Wextra -Iinclude -O2

SRC = src/generator.c src/person.c main.c
OBJ = $(SRC:.c=.o)
BIN = main

all: $(BIN)

$(BIN): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^

clean:
	rm -f $(OBJ) $(BIN)
