CFLAGS := -std=c99 -Wall -Werror -g
LIBS=-lcheck

all: ckata

ckata: src/RomanNumeralConverter.o src/RomanNumeralCalculator.o
	gcc -o ckata src/RomanNumeralConverter.o src/RomanNumeralCalculator.o

RomanNumeralConverter.o: src/RomanNumeralConverter.c src/RomanNumeralConverter.h
	gcc $(CFLAGS) -c src/RomanNumeralConverter.c

RomanNumeralCalculator.o: RomanNumeralCalculator.c RomanNumeralCalculator.h
	gcc $(CFLAGS) -c src/RomanNumeralCalculator.c

test: ckataTest
	./ckataTest

valgrindTest: ckataTest
	valgrind --leak-check=yes ./ckataTest

ckataTest: test/RomanNumeralConverterTest.o test/RomanNumeralCalculatorTest.o src/RomanNumeralConverter.o src/RomanNumeralCalculator.o
	gcc -o ckataTest src/RomanNumeralConverter.o src/RomanNumeralCalculator.o test/RomanNumeralConverterTest.o test/RomanNumeralCalculatorTest.o $(LIBS) `pkg-config --cflags --libs check`

RomanNumeralConverterTest.o: test/RomanNumeralConverterTest.c src/RomanNumeralConverter.h
	gcc -c test/RomanNumeralConverterTest.c `pkg-config --cflags --libs check`

RomanNumeralCalculatorTest.o: test/RomanNumeralCalculatorTest.c src/RomanNumeralCalculator.h
	gcc -c test/RomanNumeralCalculatorTest.c `pkg-config --cflags --libs check`

clean:
	@echo "Cleaning output files and folders...\n"
	@rm -r -f src/*.o test/*.o ckataTest ckata
