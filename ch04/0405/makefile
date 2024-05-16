CC = g++
CFLAGS = -Wall -Werror
CPPUNIT = -lcppunit

all: samp0405

samp0405: samp0405.cpp
	$(CC) $(CFLAGS) -o samp0405 samp0405.cpp $(CPPUNIT)

test: samp0405
	./samp0405

clean:
	rm -f *.o
	rm -f samp0405
	
