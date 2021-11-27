#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct {
	int *a;       /* Binary heap array. */
	int capacity; /* Max. number of elements in a. */
	int n;        /* Number of elements in a. */
} heap_t;

void heap_heapify(heap_t *h, int i)
{
	/* TODO: Replace with iterative version. */

	int largest = i;
	int left = i * 2;
	int right = left + 1;
	int tmp;

	if (left < h->n && h->a[left] > h->a[largest])
		largest = left;
	if (right < h->n && h->a[right] > h->a[largest])
		largest = right;

	if (largest == i)
		return;
	
	tmp = h->a[i];
	h->a[i] = h->a[largest];
	h->a[largest] = tmp;

	heap_heapify(h, largest);
}

void heap_init(heap_t *h, int capacity)
{
	h->capacity = capacity;
	h->n = 0;
	h->a = (int*)calloc(capacity, sizeof(int));
}

void heap_free(heap_t *h)
{
	free(h->a);
	h->a = 0;
	h->n = 0;
	h->capacity = 0;
}

void heap_build(heap_t *h, int source[], int n)
{
	int i;

	h->n = n < h->capacity ? n : h->capacity;
	memcpy(h->a, source, h->n * sizeof(int));

	for (i = h->n / 2 - 1; i >= 0; --i) 
		heap_heapify(h, i);
}

void heap_swim(heap_t *h, int i)
{
	int tmp;
	while (h->a[i/2] < h->a[i]) {
		tmp = h->a[i];
		h->a[i] = h->a[i/2];
		h->a[i/2] = tmp;
		i /= 2;
	}
}

void heap_insert(heap_t *h, int val) 
{
	if (h->n >= h->capacity)
		return;

	h->a[h->n++] = val;
	heap_swim(h, h->n-1);
}

int heap_pop(heap_t *heap)
{
	int top;

	if (heap->n == 0)
		return -9999999;
	
	top = heap->a[0];

	heap->a[0] = heap->a[--heap->n];
	heap_heapify(heap, 0);

	return top;
}

int main(int argc, char *argv[])
{
	heap_t h;

	int data[] = {1, 2, 3, 100, 120, 200};
	int n = sizeof(data) / sizeof(int);

	heap_init(&h, n);

	heap_build(&h, data, n); 

	while (h.n > 0) 
		printf("%d\n", heap_pop(&h));

	heap_free(&h); 

	return 0;
}
