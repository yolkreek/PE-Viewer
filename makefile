CC=gcc
CFLAGS=-g -Wall
TARGET=bin/result.exe

SRCS=$(wildcard src/*.c)
OBJS=$(patsubst src/%.c, build/%.o, $(SRCS))

$(TARGET): $(OBJS)
	-mkdir bin
	$(CC) -o $@ $(OBJS)

build/%.o: src/%.c
	-mkdir build
	$(CC) -c $< -o $@

clean:
	rm -rf build bin