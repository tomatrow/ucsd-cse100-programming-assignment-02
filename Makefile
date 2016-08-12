# A simple makefile for CSE 100 PA2

CC=g++
CXXFLAGS=-Wall -std=c++11 -g -gdwarf-2
LDFLAGS=-g

all: compress uncompress test

compress: BitInputStream.o BitOutputStream.o HCNode.o HCTree.o

uncompress: BitInputStream.o BitOutputStream.o HCNode.o HCTree.o

test: BitInputStream.o BitOutputStream.o HCNode.o HCTree.o

HCTree.o: BitInputStream.hpp BitOutputStream.hpp HCNode.hpp HCTree.hpp

HCNode.o: HCNode.hpp

BitOutputStream.o: BitOutputStream.hpp

BitInputStream.o: BitInputStream.hpp

run: compress uncompress
	rm -fr *.compressed *.uncompressed
	./runTests.fish justA checkpoint1.txt checkpoint2.txt justABC empty

clean:
	rm -fr compress uncompress test *.o core* *.dSYM
