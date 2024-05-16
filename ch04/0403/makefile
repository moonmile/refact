CC = gcc
CFLAGS = -Wall -Werror
CUNIT = -lcunit

all: samp0403

samp0403: samp0403.c
	$(CC) $(CFLAGS) -o samp0403 samp0403.c $(CUNIT)

test: samp0403
	./samp0403

clean:
	rm -f *.o
	rm -f samp0403
	
