# Makefile para proyecto de cocina (versión garantizada)
CC = gcc
CFLAGS = -Wall -Wextra -g -std=c99
TARGET = mc_sansano
SRCS = main.c tablero.c inventario.c acciones.c
OBJS = $(SRCS:.c=.o)
HEADERS = main.h tablero.h inventario.h acciones.h

.PHONY: all clean run

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $^ -o $@

%.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)

run: $(TARGET)
	./$(TARGET)

valgrind: $(TARGET)
	valgrind --leak-check=full --track-origins=yes ./$(TARGET)