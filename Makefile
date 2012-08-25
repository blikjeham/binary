SHELL = /bin/sh

.SUFFIXES:
.SUFFIXES: .c .o

DEBUG = -ggdb
CFLAGS = -Wall -O2 $(DEBUG)
LDFLAGS = -lcurses

COMPILE = $(CC) $(DEFS) $(DEFAULT_INCLUDES) $(INCLUDES) $(CPPFLAGS) $(CFLAGS)
LINK = $(CC) $(CFLAGS)
INSTALL = /usr/bin/install
INSTALL_PROGRAM = ${INSTALL}
INSTALL_DATA = ${INSTALL} -m 644

DEPS = config.h
DEPS += binary.h
DEPS += twin.h
DEPS += balance.h

OBJ = main.o
OBJ += binary.o
OBJ += twin.o
OBJ += balance.o

%.o: %c $(DEPS)
	$(COMPILE) -c -o $@ $<

all: binary

binary: $(OBJ)
	$(LINK) -o $@ $^ $(LDFAGS)

.PHONY: clean

clean:
	\rm -fv *.o *~ binary