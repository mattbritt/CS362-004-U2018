CFLAGS = -Wall -fpic -coverage -lm -std=c99

all: testme.c
	gcc -o testme testme.c -g $(CFLAGS)

clean:
	rm -f *.o *.gcov *.gcda *.gcno *.so *.out testme