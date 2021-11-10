# Compiler
CXX       = g++

# Flags
CXXFLAGS  = -Wall -O2 -std=c++17
GMPFLAGS  = -lgmp -lgmpxx

# Executables
EXES      = BlockPuzzle Factorial FactorialGMP Hex2Dec QuickSort

# Targets
all: $(EXES)

# Pattern Rule - Override the Built-In Implicit Rule
# https://www.gnu.org/software/make/manual/html_node/Catalogue-of-Rules.html
%: %.cpp
	@echo "==>Compiling" $<
	$(CXX)  $(CXXFLAGS)  $<  -o $@
	@echo

FactorialGMP: FactorialGMP.cpp
	@echo "==>Compiling" $<
	$(CXX)  $(CXXFLAGS)  $(GMPFLAGS)  $<  -o $@
	@echo

clean:
	rm -f $(EXES)
