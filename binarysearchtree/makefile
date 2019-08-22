# Standard compiler variables
CC = g++
CCFLAGS = -Wall -g

#rules start here
prog4: prog4.o
	$(CC) -o prog4.exe $(CFLAGS) prog4.o
	
prog4.o: prog4.cc
	$(CC) -c $(CCFLAGS) prog4.cc

clean:
	-rm *.o *.exe
