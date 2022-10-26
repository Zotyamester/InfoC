#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct header
{
	size_t size;
};

int* new_array(size_t size)
{
	struct header* data = (struct header*)malloc(sizeof(struct header) + size * sizeof(int));
	if (data == NULL)
		return NULL;

	data->size = size;
	return (int*)(data + 1);
}

void delete_array(int* arr)
{
	struct header* data = ((struct header*)arr) - 1;
	free(data);
}

size_t size_of_array(int* arr)
{
	struct header* header = ((struct header*)arr) - 1;
	return header->size;
}

int* extend_array(int* arr, size_t amount)
{
	struct header* header = ((struct header*)arr) - 1;

	size_t new_size = header->size + amount;
	struct header* new_data = (struct header*)malloc(sizeof(struct header) + new_size * sizeof(int));
	if (new_data == NULL)
		return arr;

	new_data->size = new_size;
	memcpy(new_data + 1, arr, header->size * sizeof(int));

	free(header);

	return (int*)(new_data + 1);
}

int main(void)
{
	int* vec = new_array(10);
	if (vec == NULL)
		exit(1);

	for (int i = 0; i < size_of_array(vec); i++)
		vec[i] = i + 1;

	for (int i = 0; i < size_of_array(vec); i++)
		printf("%d ", vec[i]);
	printf("\n");

	int* new_vec = extend_array(vec, 20);
	if (new_vec == vec)
		exit(2);
	vec = new_vec;

	for (int i = 0; i < size_of_array(vec); i++)
		vec[i] = size_of_array(vec) - i;

	for (int i = 0; i < size_of_array(vec); i++)
		printf("%d ", vec[i]);
	printf("\n");

	delete_array(vec);

	return 0;
}
