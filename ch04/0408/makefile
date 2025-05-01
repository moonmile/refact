CC = gcc
CFLAGS = -Wall -Werror
CUNIT = -lcunit

all: main samp0408


color.o: color.c color.h
	$(CC) $(CFLAGS) -c color.c
main.o: main.c color.h
	$(CC) $(CFLAGS) -c main.c
samp0408.o: samp0408.c color.h
	$(CC) $(CFLAGS) -c samp0408.c

main: main.o color.o
	$(CC) $(CFLAGS) -o main main.o color.o  
samp0408: samp0408.o color.o
	$(CC) $(CFLAGS) -o samp0408 samp0408.o color.o $(CUNIT)


clean:
	rm -f *.o
	rm -f main

test: samp0408
	./samp0408