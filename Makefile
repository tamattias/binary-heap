CFLAGS += -Wall -ansi -pedantic

heap: heap.c
	$(CC) $(CFLAGS) heap.c -o heap
