#Makefile
CC=cc
CFLAGS=-I
LDFLAGS=-lncurses -lm

all: 
	$(CC) -o game src/pong.c $(LDFLAGS)
