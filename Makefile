COMP=gcc
TARGET=run
CFLAGS= -ansi -pedantic -Wall -Werror
CK=-c
LDK=-o
SRC=src
MAIN=$(SRC)/main.c
ROTATE=$(SRC)/rotate.c
OPEN=$(SRC)/open.c
OFILES= main.o rotate.o open.o


BUILDDIR=build

all:link clean

link:$(OFILES)
	$(COMP) $(LDK) $(BUILDDIR)/$(TARGET) $(CFLAGS) $(OFILES) -lm 

main.o:$(MAIN)
	$(COMP) $(CK) $(MAIN)

rotate.o:$(ROTATE)
	$(COMP) $(CK) $(ROTATE)

open.o:$(OPEN)
	$(COMP) $(CK) $(OPEN)

clean: 
	rm -f $(TARGET) $(OFILES)
