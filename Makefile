CC=gcc
LD=gcc
CFLAGS=-ggdb -std=c99 -Wall
LIBS= -lm

testArrayStrings.c: testArraysStrings.o vectors.o arraysStrings.o
	$(LD) -o testArraysStrings testArraysStrings.o vectors.o arraysStrings.o $(LIBS)
	
vectors.o:	vectors.h vectors.c
	$(CC) $(CFLAGS) -c vectors.c -o vectors.o

testArraysStrings.o:	testArraysStrings.c
	$(CC) $(CFLAGS) -c testArraysStrings.c -o testArraysStrings.o

arraysStrings.o : arraysStrings.c
	$(CC) $(CFLAGS) -c arraysStrings.c -o arraysStrings.o

clean:
	rm *.o
	rm testArraysStrings 