CC=gcc
CFLAGS=-Wall -g -ansi -pedantic
LDFLAGS=-pthread

OUTPUT1=ola_threads
OUTPUT2=sushibar
SRC1=ola_threads.c
SRC2=sushibar.c

all:
	$(CC) $(CFLAGS) $(LDFLAGS) $(SRC1) -o $(OUTPUT1)
	$(CC) $(CFLAGS) $(LDFLAGS) $(SRC2) -o $(OUTPUT2)
	
clean:
	rm -fr $(OUTPUT1) $(OUTPUT2) 

