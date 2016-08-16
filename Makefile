CFLAGS := -std=c99 -Wall -Werror -g
LIBS=-lcheck

all: ckata

ckata: src/RomanNumeralConverter.o src/RomanNumeralCalculator.o
	gcc -o ckata src/RomanNumeralConverter.o src/RomanNumeralCalculator.o

RomanNumeralConverter.o: src/RomanNumeralConverter.c src/RomanNumeralConverter.h
	gcc $(CFLAGS) -c src/RomanNumeralConverter.c

RomanNumeralCalculator.o: RomanNumeralCalculator.c RomanNumeralCalculator.h
	gcc $(CFLAGS) -c src/RomanNumeralCalculator.c

test: ckata-test
	./ckata-test

ckata-test: test/RomanNumeralConverter-test.o test/RomanNumeralCalculator-test.o src/RomanNumeralConverter.o src/RomanNumeralCalculator.o
	gcc -o ckata-test src/RomanNumeralConverter.o src/RomanNumeralCalculator.o test/RomanNumeralConverter-test.o test/RomanNumeralCalculator-test.o $(LIBS) `pkg-config --cflags --libs check`

RomanNumeralConverter-test.o: test/RomanNumeralConverter-test.c src/RomanNumeralConverter.h
	gcc -c test/RomanNumeralConverter-test.c `pkg-config --cflags --libs check`

RomanNumeralCalculator-test.o: test/RomanNumeralCalculator-test.c src/RomanNumeralCalculator.h
	gcc -c test/RomanNumeralCalculator-test.c `pkg-config --cflags --libs check`

clean:
	@echo "Cleaning output files and folders...\n"
	@rm -r -f src/*.o test/*.o ckata-test ckata
