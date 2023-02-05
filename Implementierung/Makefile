CFLAGS=-O3 -g -Wall -Wextra

.PHONY: all clean
all: main
main: main.c huffman.c input_output.c tree.c printer.c heap.c testing.c shannonfano.c
	$(CC) $(CFLAGS) -o huffman $^
clean:
	rm -f main
