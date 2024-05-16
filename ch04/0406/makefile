CC = gcc
CFLAGS = -Wall -Werror
CUNIT = -lcunit

all: main samp0406

main: main.c sub.c
	$(CC) $(CFLAGS) -o main main.c sub.c

sub.o: sub.c
	$(CC) $(CFLAGS) -c sub.c

samp0406: samp0406.c sub.o
	$(CC) $(CFLAGS) -o samp0406 samp0406.c sub.o $(CUNIT)

clean:
	rm -f *.o
	rm -f main
	rm -f samp0406

test:
	./samp0406

	
