CC = gcc
CFLAGS = -Wall -Werror
CUNIT = -lcunit

all: main samp0407

main: main.c ring_buffer.c
	$(CC) $(CFLAGS) -o main main.c ring_buffer.c 
samp0407: samp0407.c ring_buffer.c
	$(CC) $(CFLAGS) -o samp0407 samp0407.c ring_buffer.c $(CUNIT)

clean:
	rm -f *.o
	rm -f main
	rm -f samp0407

test: samp0407
	./samp0407
