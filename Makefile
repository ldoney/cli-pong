#Makefile
PROGNAME = pong
OBJ = src/pong.c
LDFLAGS=-lncurses -lm

ifeq ($(PREFIX),)
    PREFIX := /usr/local
endif

all: $(PROGNAME)

$(PROGNAME): $(OBJ)
	@$(CC) -o $(PROGNAME) $(OBJ) $(LDFLAGS)

$(OBJ): Makefile

.PHONY: clean
clean:
	@rm $(PROGNAME)
