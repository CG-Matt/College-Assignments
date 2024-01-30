ASM = nasm
ASMFLAGS = -felf32
CC = gcc
CFLAGS = -no-pie -m32

.PHONY: all a1

all: a1
a1:
	$(ASM) $(ASMFLAGS) -o a1.o assignment1.asm
	$(CC) $(CFLAGS) -o assignment1 a1.o
	rm a1.o
