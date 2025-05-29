CC = gcc
CFLAGS = -Wall -Werror
CUNIT = -lcunit
OPENSSL = -lssl -lcrypto
OBJS = \
	test_main.o \
	samp0307.o \
	samp0307-2.o 

all: test_main

samp0307.o: samp0307.c
	$(CC) $(CFLAGS) -c samp0307.c $(CUNIT) $(OPENSSL)
samp0307-2.o: samp0307-2.c
	$(CC) $(CFLAGS) -c samp0307-2.c $(CUNIT) $(OPENSSL)

test_main: $(OBJS)
	$(CC) $(CFLAGS) -o test_main $(OBJS) $(CUNIT) $(DTEST) $(OPENSSL)


clean:
	rm -f *.o
	rm -f samp0307 samp0307-2

test: test_main
	./test_main
	
