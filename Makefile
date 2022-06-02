CC=gcc
CFLAGS=-Wall
SRC=./src/
INC=./inc/

SOURCES=password.c security.c utils.c account.c main.c
OBJECTS=$(SOURCES:.c=.o)

all: pwman

pwman: $(OBJECTS)
	$(CC) $(CFLAGS) -o $@ $^

%.o: $(SRC)%.c
	$(CC) $(CFLAGS) -I $(INC) -o $@ -c $<

clean:
	find . -name "*~" -delete
	find . -name "*.o" -delete

mrpropper: clean
	rm pwman
