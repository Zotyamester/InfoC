#include <stdio.h>
#include <stdlib.h>

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

int main(int argc, char* argv[])
{
	int a, b, m;
	scanf("%d %d %d", &a, &b, &m);

	//printf("a^b mod m = %d\n", modular_exponentation(a, b, m));

	printf("%dx === %d (mod %d)\n", a, b, m);

	int* solution_set = NULL;
	int size = solve_linear_congruence(a, b, m, &solution_set);
	if (size < 0)
	{
		perror("Not enough memory: ");
		return 1;
	}
	else if (size == 0)
	{
		printf("No solutions to this congruence.\n");
	}
	else
	{
		printf("Solutions (mod m):");
		for (int i = 0; i < size; i++)
		{
			printf(" %d", solution_set[i]);
		}
		printf("\n");
		free(solution_set);
		solution_set = NULL;
	}

	return 0;
}
