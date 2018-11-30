
# c++ compiler
CC = g++

# compile flags
CFLAGS = -Iinclude -Wall -std=c++11 -O2

.PHONY: all clean

all: bin/lists bin/stack bin/queue bin/dictionary

bin/lists: tests/lists.cpp
	$(CC) $(CFLAGS) $^ -o $@

bin/stack: tests/stack.cpp
	$(CC) $(CFLAGS) $^ -o $@

bin/queue: tests/queue.cpp
	$(CC) $(CFLAGS) $^ -o $@

bin/dictionary: tests/dictionary.cpp
	$(CC) $(CFLAGS) $^ -o $@

clean:
	rm -rf bin/*
