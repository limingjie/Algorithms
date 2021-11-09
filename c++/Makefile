# Compiler
CXX       = g++

# Flags
CXXFLAGS  = -Wall -O2 -std=c++17
GMPFLAGS  = -lgmp -lgmpxx

# Executables
EXES      = BlockPuzzle Factorial FactorialGMP Hex2Dec QuickSort

# Targets
all: $(EXES)

BlockPuzzle: BlockPuzzle.cpp
	@echo "==>Compiling" $<
	$(CXX)  $(CXXFLAGS)  $<  -o $@
	@echo

Factorial: Factorial.cpp
	@echo "==>Compiling" $<
	$(CXX)  $(CXXFLAGS)  $<  -o $@
	@echo

FactorialGMP: FactorialGMP.cpp
	@echo "==>Compiling" $<
	$(CXX)  $(CXXFLAGS)  $(GMPFLAGS)  $<  -o $@
	@echo

Hex2Dec: Hex2Dec.cpp
	@echo "==>Compiling" $<
	$(CXX)  $(CXXFLAGS)  $<  -o $@
	@echo

QuickSort: QuickSort.cpp Stopwatch.h
	@echo "==>Compiling" $<
	$(CXX)  $(CXXFLAGS)  $<  -o $@
	@echo

clean:
	rm -f $(EXES)
