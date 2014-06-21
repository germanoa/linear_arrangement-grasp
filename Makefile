CC=g++
CFLAGS=-Wall -g3

all: la-grasp la-grasp2 la-grasp3 la-grasp4

la-grasp: 
	$(CC) $(CFLAGS) src/la-grasp.cpp -o bin/la-grasp

la-grasp2: 
	$(CC) $(CFLAGS) src/la-grasp2.cpp -o bin/la-grasp2

la-grasp3: 
	$(CC) $(CFLAGS) src/la-grasp3.cpp -o bin/la-grasp3

la-grasp4: 
	$(CC) $(CFLAGS) src/la-grasp4.cpp -o bin/la-grasp4

clean:
	rm -f bin/la-grasp*
