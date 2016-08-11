CFLAGS=-Wall
LIBS=-lcheck

all: ckata

ckata: RomanNumeralConverter.o
	gcc -o ckata RomanNumeralConverter.o

RomanNumeralConverter.o: RomanNumeralConverter.c RomanNumeralConverter.h
	gcc $(CFLAGS) -c RomanNumeralConverter.c

test: ckata-test
	./ckata-test

ckata-test: RomanNumeralConverter-test.o RomanNumeralConverter.o
	gcc -o ckata-test RomanNumeralConverter.o RomanNumeralConverter-test.o $(LIBS) `pkg-config --cflags --libs check`

RomanNumeralConverter-test.o: RomanNumeralConverter-test.c RomanNumeralConverter.h
	gcc -c RomanNumeralConverter-test.c `pkg-config --cflags --libs check`

clean:
	@echo "Cleaning output files and folders...\n"
	@rm -r -f *.o *.o ckata-test ckata
