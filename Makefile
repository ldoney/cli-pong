#Makefile
PROGNAME = pong
OBJ = src/pong.c
LDFLAGS=-lncurses -lm

ifeq ($(PREFIX),)
    PREFIX := /usr/local/bin
endif

all: $(PROGNAME)

$(PROGNAME): $(OBJ)
	@$(CC) -o build/$(PROGNAME) $(OBJ) $(LDFLAGS)

install: $(PROGNAME)
	@cp build/$(PROGNAME) $(PREFIX)

$(OBJ): Makefile

.PHONY: clean
clean:
	@rm $(PROGNAME)
