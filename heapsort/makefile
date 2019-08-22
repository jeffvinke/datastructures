# Standard compiler variables
CC = g++
CCFLAGS = -O2

#rules start here
prog4: prog5.o
	$(CC) -o prog5.exe $(CFLAGS) prog5.o
	
prog5.o: prog5.cc
	$(CC) -c $(CCFLAGS) prog5.cc

clean:
	-rm *.o *.exe
