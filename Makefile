#
# My first Makefile, whee!
#

CXX = g++
CXXFLAGS = -pedantic -Wno-long-long -Wno-missing-field-initializers -Wall -W -Wundef -Wendif-labels -Wshadow -Wcast-align -Wwrite-strings -Wdisabled-optimization -Wold-style-cast -Woverloaded-virtual -O2 -pipe -ffor-scope -fno-gnu-keywords

.PHONY: all

all: Bst.o BST_Driver # fraction.o fracmain

# abstractarray absary

BST_Driver: Bst.o

myprogram: abstractarray.o absary.o
	$(CXX) $+ -o $@

