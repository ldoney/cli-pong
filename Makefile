#Makefile
PROGNAME = pong
OBJ = src/pong.c
LDFLAGS=-lncurses -lm

ifeq ($(PREFIX),)
    PREFIX := /usr/local/bin
endif

all: $(PROGNAME)

$(PROGNAME): $(OBJ)
	@$(CC) -o $(PROGNAME) $(OBJ) $(LDFLAGS)

install: $(PROGNAME)
	@cp pong $(PREFIX)

$(OBJ): Makefile

.PHONY: clean
clean:
	@rm $(PROGNAME)
