# Makefile for t9/trieNode program
# CSE 374 HW 5, Yunsi Mou

# default target
t9: t9.o trieNode.o
	gcc -Wall -g -std=c11 -o t9 t9.o trieNode.o

# individual source files
trieNode.o: trieNode.c trieNode.h
	gcc -Wall -g -std=c11 -c trieNode.c

t9.o: t9.c trieNode.h
	gcc -Wall -g -std=c11 -c t9.c

# remove built files and backups
clean:
	rm -f *.o t9 *~
