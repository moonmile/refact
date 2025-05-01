CC = gcc
CFLAGS = -Wall -Werror
CUNIT = -lcunit
OPENSSL = -lssl -lcrypto
OBJS = \
	test_main.o \
	samp0306.o \
	samp0306-2.o 

all: test_main

samp0306.o: samp0306.c
	$(CC) $(CFLAGS) -c samp0306 samp0306.c $(CUNIT) $(OPENSSL)
samp0306-2.o: samp0306-2.c
	$(CC) $(CFLAGS) -c samp0306-2.c $(CUNIT) $(OPENSSL)

test_main: $(OBJS)
	$(CC) $(CFLAGS) -o test_main $(OBJS) $(CUNIT) $(DTEST) $(OPENSSL)


clean:
	rm -f *.o
	rm -f samp0306 samp0306-2
	
