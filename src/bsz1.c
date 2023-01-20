#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

/// <summary>
/// Calculates a ^ b mod m with modular exponentation.
/// </summary>
/// <param name="a">The base.</param>
/// <param name="b">The exponent.</param>
/// <param name="m">The modulus.</param>
/// <returns>Returns a ^ b mod m</returns>
int modular_exponentation(int a, int b, int m)
{
	// a ^ b ≡ ? (mod m)
	a %= m;
	if (a == 0)
	{
		return 0;
	}

	int res = 1;
	int rhs = a;
	while (b > 0)
	{
		if (b & 1)
		{
			res = (res * rhs) % m;
		}

		rhs = (rhs * rhs) % m;
		b >>= 1;
	}

	return res;
}

/// <summary>
/// Calculates the greatest common divisor (GCD) of a and b with the Euclidean algorithm.
/// </summary>
/// <param name="a">First number.</param>
/// <param name="b">Second number.</param>
/// <returns>Returns the greatest common divisor (GCD) of a and b.</returns>
int get_gcd(int a, int b)
{
	while (b != 0)
	{
		int t = a % b;
		a = b;
		b = t;
	}
	return a;
}

/// <summary>
/// Solves the linear congruence ax ≡ b (mod m)
/// </summary>
/// <param name="a">The coefficient of x.</param>
/// <param name="b">The right-hand side.</param>
/// <param name="m">The modulus.</param>
/// <param name="p_solution_set">The pointer to where the solutions set (mod m)'s pointer should be.</param>
/// <returns>The size of the solution set (mod m) or minus one on error.</returns>
int solve_linear_congruence(int a, int b, int m, int** p_solution_set)
{
	int gcd = get_gcd(a, m); // the size of the solution set if it exists
	if (b % gcd != 0) // no solutions
	{
		return 0;
	}

	int* solution_set = (int*)malloc(gcd * sizeof(int));
	if (solution_set == NULL)
	{
		return -1;
	}

	int _m = m / gcd;

	int prev_a = _m;
	int prev_b = 0;
	int _a = a / gcd;
	int _b = b / gcd;

	while (_a != 1) // until the coefficient of x is 1
	{
		int t_a = prev_a % _a;
		int t_b = prev_b - _b * (prev_a / _a);
		prev_a = _a;
		prev_b = _b;
		_a = t_a;
		_b = t_b;
	}

	if (_b < 0)
	{
		_b += _m;
	}

	solution_set[0] = _b % _m;
	for (int i = 1; i < gcd; i++)
	{
		solution_set[i] = solution_set[i - 1] + _m;
	}

	*p_solution_set = solution_set;
	return gcd;
}

typedef struct Matrix
{
	float* data;
	float** matrix;
	size_t k, n;
} Matrix;

bool matrix_init(Matrix* m, size_t k, size_t n)
{
	float* data = (float*)malloc(k * n * sizeof(float));
	if (data == NULL)
		return false;

	float** matrix = (float**)malloc(k * sizeof(float*));
	if (matrix == NULL)
	{
		free(data);
		return false;
	}

	for (size_t i = 0; i < k; i++)
		matrix[i] = data + i * n;

	m->data = data;
	m->matrix = matrix;
	m->k = k;
	m->n = n;

	return true;
}

void matrix_free(Matrix* m)
{
	free(m->matrix);
	free(m->data);
}

bool matrix_read(Matrix* m, FILE* file)
{
	size_t k, n;
	if (fscanf(file, "%llu %llu", &k, &n) != 2)
		return false;

	if (!matrix_init(m, k, n))
		return false;

	for (size_t i = 0; i < m->k; i++)
	{
		for (size_t j = 0; j < m->n; j++)
		{
			if (fscanf(file, "%f", &m->matrix[i][j]) != 1)
			{
				matrix_free(m);
				return false;
			}
		}
	}

	return true;
}

bool matrix_write(const Matrix* m, FILE* file)
{
	if (fprintf(file, "%llu %llu\n\n", m->k, m->n) < 0)
		return false;

	for (size_t i = 0; i < m->k; i++)
	{
		for (size_t j = 0; j < m->n; j++)
			if (fprintf(file, "%.1f ", m->matrix[i][j]) < 0)
				return false;
		if (fputc('\n', file) == EOF)
			return false;
	}

	return true;
}

bool matrix_multiply(const Matrix* a, const Matrix* b, Matrix* c)
{
	size_t k = a->k, n = a->n, m = b->n;

	if (a->n != b->k || !matrix_init(c, a->k, b->n))
		return false;

	for (size_t i = 0; i < k; i++)
	{
		for (size_t j = 0; j < m; j++)
		{
			float cell_value = 0;
			for (size_t idx = 0; idx < n; idx++)
				cell_value += a->matrix[i][idx] * b->matrix[idx][j];
			c->matrix[i][j] = cell_value;
		}
	}

	return true;
}

bool matrix_gauss(Matrix* m)
{
	if (m->k != m->n)
		return false;

	int i = 0, j = 0;
	while (i < m->k)
	{
		if (m->matrix[i][j] == 0)
		{
			int new_i = i + 1;
			while (new_i < m->k && m->matrix[new_i][j] == 0)
				new_i++;
			if (new_i == m->k)
			{
				if (j == m->n - 1)
				{
					break;
				}
				else
				{
					j++;
					continue;
				}
			}

			for (int col_idx = 0; col_idx < m->n; col_idx++)
			{
				float tmp = (float)m->matrix[i][j];
				m->matrix[i][col_idx] = m->matrix[new_i][col_idx];
				m->matrix[new_i][col_idx] = tmp;
			}
		}

		float divisor = (float)m->matrix[i][j];
		for (int col_idx = j; col_idx < m->n; col_idx++)
			m->matrix[i][col_idx] /= divisor;

		for (int row_idx = i + 1; row_idx < m->k; row_idx++)
		{
			float lambda = (float)m->matrix[row_idx][j];
			for (int col_idx = j; col_idx < m->n; col_idx++)
				m->matrix[row_idx][col_idx] -= lambda * m->matrix[i][col_idx];
		}

		i++;
		j++;
	}

	return true;
}

int main(int argc, char* argv[])
{
	//int a, b, m;
	//scanf("%d %d %d", &a, &b, &m);

	////printf("a^b mod m = %d\n", modular_exponentation(a, b, m));

	//printf("%dx === %d (mod %d)\n", a, b, m);

	//int* solution_set = NULL;
	//int size = solve_linear_congruence(a, b, m, &solution_set);
	//if (size < 0)
	//{
	//	perror("Not enough memory: ");
	//	return 1;
	//}
	//else if (size == 0)
	//{
	//	printf("No solutions to this congruence.\n");
	//}
	//else
	//{
	//	printf("Solutions (mod m):");
	//	for (int i = 0; i < size; i++)
	//	{
	//		printf(" %d", solution_set[i]);
	//	}
	//	printf("\n");
	//	free(solution_set);
	//	solution_set = NULL;
	//}

	/*Matrix a, b, c;

	matrix_read(&a, stdin);
	matrix_read(&b, stdin);

	matrix_multiply(&a, &b, &c);

	matrix_write(&c, stdout);

	matrix_free(&c);

	matrix_free(&b);
	matrix_free(&a);*/

	Matrix m;

	matrix_read(&m, stdin);

	matrix_gauss(&m);

	matrix_write(&m, stdout);

	matrix_free(&m);

	return 0;
}
