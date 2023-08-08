#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include "debugmalloc.h"

typedef struct KeyValTree
{
	char key, value;
	struct KeyValTree* left, * right;
} KeyValTree;

void kvt_insert(KeyValTree** ptree, char key, char value)
{
	if (*ptree == NULL)
	{
		KeyValTree* node = (KeyValTree*)malloc(sizeof(KeyValTree));
		if (node == NULL)
			return;
		node->left = node->right = NULL;
		node->key = key;
		node->value = value;

		*ptree = node; /* we found a place for the key-value pair */
	}
	else if ((*ptree)->key < key)
	{
		kvt_insert(&(*ptree)->right, key, value); /* should insert to the left subtree */
	}
	else if ((*ptree)->key > key)
	{
		kvt_insert(&(*ptree)->left, key, value); /* should insert to the right subtree */
	}
	else
	{
		(*ptree)->value = value; /* just modify the value corresponding to the key */
	}
}

void kvt_print_asc(KeyValTree** ptree)
{
	if (*ptree == NULL)
		return;

	kvt_print_asc(&(*ptree)->left);
	putchar((*ptree)->value);
	kvt_print_asc(&(*ptree)->right);
}

void kvt_free(KeyValTree** ptree)
{
	if (*ptree == NULL)
		return;
	kvt_free(&(*ptree)->left);
	kvt_free(&(*ptree)->right);
	free(*ptree);
}

int main(void) {
	const char pattern[][2] = {
		{13, 105}, {22, 116}, {14, 111}, {45, 101}, {3, 99},
		{35, 32}, {23, 32}, {65, 32}, {18, 10}, {53, 97}, {17, 62},
		{27, 110}, {55, 33}, {15, 46}, {4, 108}, {59, 41}, {72, 32},
		{41, 102}, {6, 100}, {39, 110}, {60, 59}, {68, 116}, {31, 10},
		{74, 59}, {30, 123}, {63, 32}, {1, 105}, {16, 104}, {47, 108},
		{66, 114}, {28, 40}, {20, 105}, {26, 105}, {62, 32}, {29, 41},
		{46, 108}, {71, 110}, {25, 97}, {7, 101}, {64, 32}, {0, 35},
		{77, 10}, {50, 118}, {76, 125}, {56, 92}, {5, 117}, {34, 32},
		{48, 111}, {38, 105}, {8, 32}, {54, 103}, {19, 10}, {33, 32},
		{73, 48}, {32, 32}, {61, 10}, {51, 105}, {12, 100}, {36, 112},
		{67, 101}, {37, 114}, {44, 72}, {70, 114}, {58, 34}, {9, 60},
		{2, 110}, {52, 108}, {11, 116}, {10, 115}, {75, 10}, {24, 109},
		{40, 116}, {21, 110}, {49, 32}, {42, 40}, {43, 34}, {57, 110},
		{69, 117}, {78, 0}
	};
	const size_t count = sizeof(pattern) / sizeof(pattern[0]);


	KeyValTree* tree = NULL;

	for (int i = 0; i < count; i++)
		kvt_insert(&tree, pattern[i][0], pattern[i][1]);

	kvt_print_asc(&tree);

	kvt_free(&tree);

	return 0;
}
