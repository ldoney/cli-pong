#Makefile
PROGNAME = pong
OBJ = src/pong.c
LDFLAGS=-lncurses -lm

ifeq ($(PREFIX),)
    PREFIX := /usr/local/bin
endif

all: $(PROGNAME)

$(PROGNAME): $(OBJ)
	@echo Making build directory...
	@if test -d "build" ; then echo Build directory exists!; else mkdir build; fi
	@echo Building c program...
	@$(CC) -o build/$(PROGNAME) $(OBJ) $(LDFLAGS)
	@echo Done!

install: $(PROGNAME)
	@echo Copying program to PATH...
	@cp build/$(PROGNAME) $(PREFIX)
	@echo Done!

$(OBJ): Makefile

.PHONY: clean
clean:
	@echo Cleaning project...
	@rm $(PROGNAME)
	@echo Done!
