CFLAGS := -std=c99 -Wall -Werror -g
LIBS=-lcheck

all: ckata

ckata: RomanNumeralConverter.o RomanNumeralCalculator.o
	gcc -o ckata RomanNumeralConverter.o RomanNumeralCalculator.o

RomanNumeralConverter.o: RomanNumeralConverter.c RomanNumeralConverter.h
	gcc $(CFLAGS) -c RomanNumeralConverter.c

RomanNumeralCalculator.o: RomanNumeralCalculator.c RomanNumeralCalculator.h
	gcc $(CFLAGS) -c RomanNumeralCalculator.c

test: ckata-test
	./ckata-test

ckata-test: RomanNumeralConverter-test.o RomanNumeralCalculator-test.o RomanNumeralConverter.o RomanNumeralCalculator.o
	gcc -o ckata-test RomanNumeralConverter.o RomanNumeralCalculator.o RomanNumeralConverter-test.o RomanNumeralCalculator-test.o $(LIBS) `pkg-config --cflags --libs check`

RomanNumeralConverter-test.o: RomanNumeralConverter-test.c RomanNumeralConverter.h
	gcc -c RomanNumeralConverter-test.c `pkg-config --cflags --libs check`

RomanNumeralCalculator-test.o: RomanNumeralCalculator-test.c RomanNumeralCalculator.h
	gcc -c RomanNumeralCalculator-test.c `pkg-config --cflags --libs check`

clean:
	@echo "Cleaning output files and folders...\n"
	@rm -r -f *.o *.o ckata-test ckata
