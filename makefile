all: q1 q2

q1: q1.c
    gcc -Wall -std=c99 -pedantic -o q1 q1.c

q2: q2.c
    gcc -Wall -std=c99 -pedantic -o q2 q2.c

clean:
	rm *.o
	rm *q1
	rm*q2