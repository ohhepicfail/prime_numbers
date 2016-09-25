CFLAGS=-c -Wall -Wextra -Wpedantic -std=c++14 

all: nprime find_super_prime mr

nprime: nprime.o sieve.o
	g++ nprime.o sieve.o -o nprime

find_super_prime: find_super_prime.o sieve.o
	g++ find_super_prime.o sieve.o -o find_super_prime

mr: mr.o sieve.o
	g++ mr.o sieve.o -o mr

nprime.o: nprime.cpp
	g++ $(CFLAGS) nprime.cpp

sieve.o: sieve.cpp
	g++ $(CFLAGS) sieve.cpp

find_super_prime.o: find_super_prime.cpp
	g++ $(CFLAGS) find_super_prime.cpp

mr.o: mr.cpp
	g++ $(CFLAGS) mr.cpp

clean:
	rm -rf *.o prime
