##
## Algorithm Practice - MinGW Makefile
##
## Mingjie Li (limingjie0719@gmail.com)
## Mar 13, 2014
##

# Compiler
CC        = gcc
CXX       = g++

# Flags
CXXFLAGS  = -Wall -O2

# Executables
EXES      = BinarySearchTree.exe QuickSort.exe BlockPuzzle.exe

# Targets
all: $(EXES)

%.exe: %.cpp
	@echo "==>Compiling" $<
	$(CXX)  $(CXXFLAGS)  -o $@  $<
	@echo

clean:
	rm -f $(EXES)
