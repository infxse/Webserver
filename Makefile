CC = gcc
CFLAGS = -Wall -Wextra -g -fsanitize=address -Isrc
LDFLAGS = -fsanitize=address

SRC = src/main.c src/server.c src/http.c src/file.c
OBJ = $(SRC:.c=.o)

help:
	@echo "Usage: make <command>"
	@echo ""
	@echo "  build     Compile changed files and link the binary"
	@echo "  rebuild   Clean everything and compile from scratch"
	@echo "  clean     Remove all .o files and the server binary"
	@echo "  help      Show this help"

build: $(OBJ)
	$(CC) $(LDFLAGS) -o server $(OBJ)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

rebuild: clean build

clean:
	rm -f $(OBJ) server

.PHONY: help ? build rebuild clean

?: help