CC = g++
CPPFLAGS = -g -pedantic -Wall
CFLAGS = -pedantic
CLINK = -lglut -lGL -lGLU -lGLEW

all: argon anim 

anim: anim.cpp
	$(CC) $(CFLAGS) anim.cpp $(CLINK) -o anim

argon: main.o argon.o vector.o
	$(CC) $(CPPFLAGS) main.o argon.o vector.o -o argon

main.o: main.cpp
	$(CC) $(CPPFLAGS) -c main.cpp

argon.o: argon.cpp
	$(CC) $(CPPFLAGS) -c argon.cpp

vector.o: vector.cpp
	$(CC) $(CPPFLAGS) -c vector.cpp

del:
	rm *.dat

clean:
	rm -rf *.o *.dat argon anim 
