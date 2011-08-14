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

$(BINS):
	$(CC) $^ -o $@

%.o: %.c
	$(CC) $< -c $(CFLAGS) -o $@

clean:
	rm -f *.o $(BINS)

