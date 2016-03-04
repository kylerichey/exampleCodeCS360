# Makefile for echo client and server

CXX=			g++ $(CCFLAGS)




LIBS=

CCFLAGS= -g

all:    client

client: client.c
	g++ -o client client.cpp

clean:
	rm -f client client.o

realclean:
	rm -f $(OBJS) $(OBJS:.o=.d)  client