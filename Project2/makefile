# Makefile for the separa program

# Compiler
CC = gcc

# Compiler flags
CFLAGS = -Wall

# Target executable name
TARGET = separa

# Source files
SOURCES = separa.c

# Object files
OBJECTS = $(SOURCES:.c=.o)

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CC) $(CFLAGS) -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -c $<

clean:
	rm -f $(OBJECTS) $(TARGET)

.PHONY: all clean
