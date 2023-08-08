#include <stdio.h>
#include <stdlib.h>

typedef struct {
	int* data;
	size_t size, capacity;
} heap;

void heap_init(heap* h)
{
	h->data = NULL;
	h->size = 0;
	h->capacity = 0;
}

void heap_free(heap* h)
{
	free(h->data);
}

void heap_extend(heap* h)
{
	size_t new_capacity = h->capacity * 2 + 1;

	int* new_data = (int*)malloc(new_capacity * sizeof(int));
	if (new_data == NULL)
		return; /* should panic */
	
	for (size_t i = 0; i < h->size; i++)
		new_data[i] = h->data[i];

	free(h->data);
	h->data = new_data;
	h->capacity = new_capacity;
}

void int_swap(int* pa, int* pb)
{
	int tmp = *pa;
	*pa = *pb;
	*pb = tmp;
}

void heap_up(heap* h)
{
	size_t i = h->size - 1, j = (i - 1) / 2;
	while (i > 0 && h->data[i] > h->data[j])
	{
		int_swap(&h->data[i], &h->data[j]);
		i = j;
		j = (i - 1) / 2;
	}
}

void heap_insert(heap* h, int value)
{
	if (h->size == h->capacity)
		heap_extend(h);
	h->data[h->size++] = value;
	heap_up(h);
}

void heap_down(heap* h)
{
	size_t i = 0;
	for (;;)
	{
		size_t left = i * 2 + 1, right = i * 2 + 2;

		size_t max = (right >= h->size || h->data[left] > h->data[right]) ? left : right;
		if (max >= h->size || h->data[i] > h->data[max])
			break;
		int_swap(&h->data[i], &h->data[max]);

		i = max;
	}
}

int heap_delete_max(heap* h)
{
	int max_value = h->data[0];
	h->data[0] = h->data[--h->size];
	heap_down(h);
	return max_value;
}

void heap_print(heap* h)
{
	for (size_t i = 0; i < h->size; i++)
		printf("%d ", h->data[i]);
	putchar('\n');
}

int main(int argc, char* argv[])
{
	heap h;
	heap_init(&h);
	heap_insert(&h, 1);
	heap_insert(&h, 5);
	heap_insert(&h, 2);
	heap_insert(&h, 4);
	heap_insert(&h, 3);
	for (int i = 1; i <= 5; i++)
	{
		heap_print(&h);
		printf("\tmax=%d\n", heap_delete_max(&h));
	}

	heap_free(&h);

	return 0;
}
