CC = gcc
CFLAGS = -std=gnu99 -Wall -g -c
EXECS = server client

all: $(EXECS)

server: server.o utility.o
	$(CC) server.o utility.o -o server

server.o: server.c
	$(CC) $(CFLAGS) server.c

utility.o: utility.c utility.h
	$(CC) $(CFLAGS) utility.c
	
client: client.o c_util.o
	$(CC) client.o c_util.o -o client

client.o: client.c
	$(CC) $(CFLAGS) client.c

c_util.o: c_util.c c_util.h
	$(CC) $(CFLAGS) c_util.c

clean:
	$(RM) *.o $(EXECS)
