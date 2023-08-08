#include <stdio.h>
#include <stdlib.h>

int sum_up_to_d(int n, int d)
{
	if (n == 0)
		return d == 0;

	int count = 0;
	for (int i = 0; i <= d; i++)
		count += sum_up_to_d(n - 1, d - i);

	return count;
}

int gen_vec_n_of_sum_d(int** vecs, int size, int idx, int i, int n, int d)
{
	if (i == n)
	{
		if (d == 0)
		{
			if (idx + 1 < size)
				for (int j = 0; j < n; j++)
					vecs[idx + 1][j] = vecs[idx][j];
			idx++;
		}
	}
	else
	{
		for (int j = 0; j <= d; j++)
		{
			vecs[idx][i] = j;
			idx = gen_vec_n_of_sum_d(vecs, size, idx, i + 1, n, d - j);
		}
	}
	return idx;
}

int all_vec_n_of_sum_d(int*** pvecs, int n, int d)
{
	int count = sum_up_to_d(n, d);

	int** vecs = (int**)malloc(count * sizeof(int*));
	if (vecs == NULL)
		return -1;

	for (int i = 0; i < count; i++)
	{
		int* vec = (int*)malloc(n * sizeof(int));
		if (vec == NULL)
		{
			for (int j = 0; j < i; j++)
				free(vecs[j]);
			free(vecs);
			return -1;
		}

		vecs[i] = vec;
	}

	gen_vec_n_of_sum_d(vecs, count, 0, 0, n, d);

	*pvecs = vecs;
	return count;
}

int main(void)
{
	/* parameters */

	const int n = 3, d = 2;

	/* generate combinations*/

	int** vecs;
	int count = all_vec_n_of_sum_d(&vecs, n, d);
	if (count == -1)
	{
		perror("An unexpected error occured");
		return 1;
	}

	/* write out every combination */

	for (int i = 0; i < count; i++)
	{
		for (int j = 0; j < n; j++)
			printf("%d ", vecs[i][j]);
		printf("\n");
	}

	/* do some other things and then finally cleanup */

	for (int i = 0; i < count; i++)
		free(vecs[i]);
	free(vecs);

	return 0;
}
