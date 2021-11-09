# Compiler
CC        = gcc

# Flags
CFLAGS    = -Wall -O2 -std=c17
GMPFLAGS  = -lgmp

# Executables
EXES      = Calc SinX

# Targets
all: $(EXES)

Calc: Calc.c
	@echo "==>Compiling" $<
	$(CC)  $(CFLAGS)  $<  -o $@
	@echo

SinX: SinX.c
	@echo "==>Compiling" $<
	$(CC)  $(CFLAGS)  $<  -o $@
	@echo

clean:
	rm -f $(EXES)
