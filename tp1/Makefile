CC = gcc
CFLAGS = -Wall -Werror -W  -g
LDFLAGS = 

SRC = $(wildcard *.c)
OBJ = $(SRC:.c=.o)
EXEC=lance

all: $(EXEC)

lance:  $(OBJ)
	$(CC) $(LDFLAGS) -o $@ $^

#pour les .h

#pour les .h

%.o: %.c
	@$(CC)$(CFLAGS) -o $@ -c $< 

.PHONY: clean mrproper

clean:
	rm *.o

mrproper: clean
	rm $(EXEC)
