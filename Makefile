COMP=gcc
TARGET=sepia
TARGET_SSE=sepia_sse
CFLAGS= -ggdb -ansi -pedantic -Wall -Werror -fPIC
CK=-c
LDK=-o
SRC=src
SSE=$(SRC)/sse.asm
ASM=nasm
ASMFLAGS=-f -g elf64
MAIN=$(SRC)/main.c
SEPIA=$(SRC)/sepia.c
SEPIA_SSE=$(SRC)/sepia_sse.c
OPEN=$(SRC)/open.c
OFILES_SSE= main.o sepia_sse.o open.o sse.o
OFILES= main.o sepia.o open.o
BUILDDIR=build

all: link_sse clean

link:$(OFILES)
	$(COMP) $(LDK) $(BUILDDIR)/$(TARGET) $(CFLAGS) $(OFILES) -lm 

link_sse:$(OFILES_SSE)
	$(COMP) $(LDK) $(BUILDDIR)/$(TARGET_SSE) $(CFLAGS) $(OFILES_SSE) -lm

main.o:$(MAIN)
	$(COMP) $(CK) $(MAIN)

sepia.o:$(SEPIA)
	$(COMP) $(CK) $(SEPIA)

sepia_sse.o:$(SEPIA_SSE)
	$(COMP) -fPIC $(CK) $(SEPIA_SSE)

open.o:$(OPEN)
	$(COMP) $(CK) $(OPEN)

sse.o:$(SSE)
	$(ASM) $(ASMFLAGS) $(SSE) -o sse.o

clean: 
	rm -f $(TARGET) $(OFILES)
