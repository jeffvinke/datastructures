# Standard compiler variables
CC = g++
CCFLAGS = -g

#rules start here
prog6: prog6.o hTable.o hTable.h Entry.h
	$(CC) -o prog6.exe $(CFLAGS) prog6.o hTable.o
	
prog6.o: prog6.cc Entry.h hTable.h
	$(CC) -c $(CCFLAGS) prog6.cc

hTable.o: hTable.cc hTable.h
	$(CC) -c $(CCFLAGS) hTable.cc
clean:
	-rm *.o *.exe
