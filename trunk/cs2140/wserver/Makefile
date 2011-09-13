#
# Makefile for wserver
#

CC=gcc
CFLAGS=-g -Wall
LDFLAGS=
BINS=wserver

.PHONY: all clean

all: $(BINS)

wserver: wserver.o http_support.o
wserver.o: wserver.c http_support.h
http_support.o: http_support.c

$(BINS):
	$(CC) $^ -o $@

%.o:
	$(CC) $< -c $(CFLAGS) -o $@

clean:
	rm -f *.o $(BINS)

