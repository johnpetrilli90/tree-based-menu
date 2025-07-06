# Makefile for PC simulation of OLED menu system

CC = gcc
CFLAGS = -Wall -std=c99

# Source files
SRC = main.c menu.c menu_generated.c menu_callbacks.c oled_sim.c
OBJ = $(SRC:.c=.o)

# Output binary
TARGET = menu_sim

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -c $<

clean:
	rm -f $(OBJ) $(TARGET) *.bmp

.PHONY: all clean
