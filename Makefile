COMP=gcc
TARGET=main
CFLAGS= -ansi -pedantic -Wall -Werror
CK= -c
LDK= -o
MAIN=main.c
ROTATE=rotate.c
OFILES= main.o rotate.o
SRC=src

BUILDDIR=build


main: 
	$(COMP) $(CK) $(SRC)/$(MAIN) $(SRC)/$(ROTATE)

	$(COMP) $(LDK) $(TARGET) $(CFLAGS) $(OFILES) -lm 
clean: 
	rm -f $(TARGET) $(OFILES)
