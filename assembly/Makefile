# Makefile to assemble and link main.asm into a 32-bit Linux binary

main: main.o
	ld -m elf_i386 main.o -o run_main

# Assemble main.asm to main.o
main.o: main.asm
	nasm -f elf32 main.asm -o main.o

all: clean main

# Clean build files
clean:
	@echo "Cleaning up..."
	@rm -f main.o run_main main_copy.o