# Standard compiler variables
CC = g++
CCFLAGS = -Wall -g

#rules start here
prog3: prog3.o
	$(CC) -o prog3.exe $(CFLAGS) prog3.o
	
prog3.o: prog3.cc
	$(CC) -c $(CCFLAGS) prog3.cc

clean:
	-rm *.o *.exe
