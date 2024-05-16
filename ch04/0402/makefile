CC = gcc
CFLAGS = -Wall -Werror
CUNIT = -lcunit

all: samp0402

samp0402: samp0402.c
	$(CC) $(CFLAGS) -o samp0402 samp0402.c $(CUNIT)

test: samp0402
	./samp0402

clean:
	rm -f *.o
	rm -f samp0402
	
