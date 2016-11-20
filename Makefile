COMP=gcc
TARGET=main
CFLAGS= -ansi -pedantic -Wall -Werror
CK= -c
LDK= -o
FILES=main.c
OFILES= main.o

VPATH = src
BUILDDIR = build


main: main.c
	$(COMP) $(LDK) $(BUILDDIR)/$(TARGET) $(VPATH)/$(FILES)

#	$(COMP) $(LDK) $(TARGET) $(CFLAGS) $(OFILES) -lm 
clean: 
	rm -f $(TARGET) $(OFILES)
