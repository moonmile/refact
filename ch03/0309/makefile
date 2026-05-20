CC     = gcc
CFLAGS = -Wall -Werror
CUNIT  = -lcunit
OPENSSL = -lssl -lcrypto
OBJS   = test_main.o qrcode_url.o test_qrcode_url.o

all: test_main

qrcode_url.o: qrcode_url.c qrcode_url.h
	$(CC) $(CFLAGS) -c qrcode_url.c $(OPENSSL)

test_qrcode_url.o: test_qrcode_url.c qrcode_url.h
	$(CC) $(CFLAGS) -c test_qrcode_url.c $(CUNIT)

test_main.o: test_main.c
	$(CC) $(CFLAGS) -c test_main.c $(CUNIT)

test_main: $(OBJS)
	$(CC) $(CFLAGS) -o test_main $(OBJS) $(CUNIT) $(OPENSSL)

clean:
	rm -f *.o test_main

test: test_main
	./test_main
