# Compiler
CC        = gcc

# Flags
CFLAGS    = -Wall -O2 -std=c17
GMPFLAGS  = -lgmp

# Executables
EXES      = Calc SinX

# Targets
all: $(EXES)

# Pattern Rule - Override the Built-In Implicit Rule
# https://www.gnu.org/software/make/manual/html_node/Catalogue-of-Rules.html
%: %.c
	@echo "==>Compiling" $<
	$(CC)  $(CFLAGS)  $<  -o $@
	@echo

clean:
	rm -f $(EXES)
