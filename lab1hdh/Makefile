# Default target: compile all
all: calc

# Compile calc executable from object files
calc: calc.o calculator.o
	gcc -o calc calc.o calculator.o -lm

# Compile calc.c into calc.o object file
calc.o: calc.c calculator.h
	gcc -c calc.c -o calc.o

# Compile calculator.c into calculator.o object file
calculator.o: calculator.c calculator.h
	gcc -c calculator.c -o calculator.o

# Clean target: remove object files and executable
clean:
	rm -f calc calc.o calculator.o

