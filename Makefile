CC = gcc -c
LD = gcc
CFLAGS = -Wall -Wextra -std=c99

build: tema1
	
tema1: main.o list.o hash.o dns.o
	$(LD) $(CFLAGS) $^ -o $@
	
main.o: main.c dns.h hash.h list.h
	$(CC) $(CFLAGS) $< -o $@

list.o: list.c list.h
	$(CC) $(CFLAGS) $< -o $@

hash.o: hash.c hash.h list.h
	$(CC) $(CFLAGS) $< -o $@

dns.o: dns.c dns.h hash.h list.h
	$(CC) $(CFLAGS) $< -o $@
	
clean:
	rm -rf tema1
	rm -rf *.o
	rm -rf *~

