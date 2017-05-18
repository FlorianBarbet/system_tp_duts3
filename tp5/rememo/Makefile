CC=gcc
CFLAGS=-Werror -W -Wall -g
LDFLAGS= 

SRC = $(wildcard *.c)
OBJ = $(SRC:.c=.o)
EXEC = lance

all:$(EXEC)

lance : $(OBJ)
	$(CC) $(LDFLAGS) -o $@ $^
	chmod 777 *



%.o:%.c
	$(CC) $(CFLAGS) -o $@ -c $<

.PHONY: clean mrproper

clean :
	rm -rf *.o
mrproper: clean
	rm -rf $(EXEC)


