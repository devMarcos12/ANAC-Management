# Makefile simples
CC = gcc
CFLAGS = -Wall -Wextra -g
TARGET = grafos

all: $(TARGET)

$(TARGET): aeroporto.c grafo.c main.c
	$(CC) $(CFLAGS) -o $(TARGET) aeroporto.c grafo.c main.c

clean:
	rm -f $(TARGET) *.exe

run: $(TARGET)
	./$(TARGET)

.PHONY: all clean run