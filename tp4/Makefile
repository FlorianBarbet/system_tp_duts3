CC = gcc
CFLAGS = -Wall -Werror -W  -g
LDFLAGS = 

SRC = $(wildcard *.c)
OBJ = $(SRC:.c=.o)
EXEC=chaines

all: $(EXEC)

chaines: $(OBJ)
	$(CC) $(LDFLAGS) -o $@ $^

#pour les .h
main.o : tp4.h
#pour les .h

%.o : %.c
	$(CC) $(CFLAGS) -o $@ -c $< 

.PHONY: clean mrproper

clean:
	rm *.o

mrproper: clean
	rm $(EXEC)
