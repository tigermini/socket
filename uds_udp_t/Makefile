
CFLAGS += -g3 -Wall

all: build

build: client server

client: client.c
	$(CC) $(CFLAGS) -o $@ $<

server: server.c
	$(CC) $(CFLAGS) -o $@ $<

clean:
	rm -rf client server

.PHONY: all build client server clean