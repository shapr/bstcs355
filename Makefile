#
# My first Makefile, whee!
#

CXX = g++
CXXFLAGS = -pedantic -Wno-long-long -Wno-missing-field-initializers -Wall -W -Wundef -Wendif-labels -Wshadow -Wcast-align -Wwrite-strings -Wdisabled-optimization -Wold-style-cast -Woverloaded-virtual -g -pipe -ffor-scope -fno-gnu-keywords

.PHONY: all

all: Bst.o TestBst BST_Driver

# abstractarray absary

BST_Driver: Bst.o

TestBst: Bst.o

myprogram: abstractarray.o absary.o
	$(CXX) $+ -o $@

