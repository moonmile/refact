CC = g++
CFLAGS = -Wall -Werror
CPPUNIT = -lcppunit

all: samp0404

samp0404: samp0404.cpp
	$(CC) $(CFLAGS) -o samp0404 samp0404.cpp $(CPPUNIT)

test: samp0404
	./samp0404

clean:
	rm -f *.o
	rm -f samp0404
	
