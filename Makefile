
# c++ compiler
CC = g++

# compile flags
CFLAGS = -Iinclude -Wall -std=c++11 -O2

# directories
SDIR = tests
BDIR = bin

# targets
TARGETS = lists         \
          stack         \
          queue         \
          deque         \
          hashtable     \
          binarytree    \
          tree          \
          priorityqueue \
          graph         \
          searchtree

# source files
SRC = $(patsubst %, $(SDIR)/%.cpp, $(TARGETS))

# executable files
BIN = $(patsubst %, $(BDIR)/%, $(TARGETS))

.PHONY: all clean

all: $(BIN)

$(BDIR)/%: $(SDIR)/%.cpp
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -rf $(BDIR)/*

