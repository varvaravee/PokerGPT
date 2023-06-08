# Makefile: simple clock server with corresponding client
# PokerGPT

GTKINC  = `pkg-config --cflags gtk+-2.0`
GTKLIBS = `pkg-config --libs gtk+-2.0`

# general compiler flags
CFLAGS  = -Wall -std=c11 $(DEBUG) $(GTKINC) -c
LFLAGS  = -Wall -std=c11 $(DEBUG) $(GTKLIBS) 

# targets
all: PokerClient PokerServer

clean:
	rm -f *.o
	rm -f PokerClient PokerServer
 

PokerClient.o: PokerClient.c
	gcc PokerClient.c $(CFLAGS) -o PokerClient.o

PokerClient: PokerClient.o
	gcc PokerClient.o $(LFLAGS) -o PokerClient

cards2.o: cards2.c cards2.h
	gcc cards2.c $(CFLAGS) -o cards2.o

PokerServer.o: PokerServer.c cards2.h
	gcc PokerServer.c $(CFLAGS) -o PokerServer.o

PokerServer: PokerServer.o cards2.o
	gcc PokerServer.o cards2.o $(LFLAGS) -o PokerServer

# EOF
