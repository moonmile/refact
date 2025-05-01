CC = gcc
CFLAGS = -Wall -Werror
CUNIT = -lcunit

all: main samp0409


sleep_demo.o: sleep_demo.c sleep_demo.h
	$(CC) $(CFLAGS) -c sleep_demo.c
main.o: main.c 
	$(CC) $(CFLAGS) -c main.c
samp0409.o: samp0409.c sleep_demo.h
	$(CC) $(CFLAGS) -c samp0409.c


main: main.o sleep_demo.o
	$(CC) $(CFLAGS) -o main main.o sleep_demo.o
samp0409: samp0409.o sleep_demo.o
	$(CC) $(CFLAGS) -o samp0409 samp0409.o sleep_demo.o $(CUNIT)

clean:
	rm -f *.o
	rm -f main
	rm -f samp0409

test: samp0409
	./samp0409

