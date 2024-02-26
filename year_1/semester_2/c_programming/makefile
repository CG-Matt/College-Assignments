ASM = nasm
ASMFLAGS = -felf32
CC = gcc
CFLAGS = -no-pie -m32

.PHONY: all a1 a2 a3

all: a1 a2 a3

a1:
	$(ASM) $(ASMFLAGS) -o a1.o assignment1.asm
	$(CC) $(CFLAGS) -o assignment1 a1.o
	rm a1.o

a2:
	$(ASM) $(ASMFLAGS) -o a2p1.o assignment2_part1.asm
	$(ASM) $(ASMFLAGS) -o a2p2.o assignment2_part2.asm
	$(CC) $(CFLAGS) -o assignment2_part1 a2p1.o
	$(CC) $(CFLAGS) -o assignment2_part2 a2p2.o
	rm a2p1.o
	rm a2p2.o

a3:
	$(ASM) $(ASMFLAGS) -o a3.o assignment3.asm
	$(CC) $(CFLAGS) -o assignment3 a3.o
	rm a3.o
