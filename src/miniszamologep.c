#include <stdio.h>
#include <stdbool.h>
#include <math.h>

int main(int argc, char* argv[])
{
	double operand1, operand2;
	char operator;

	if (argc != 4 ||
		sscanf(argv[1], "%lf", &operand1) != 1 ||
		sscanf(argv[3], "%lf", &operand2) != 1 ||
		sscanf(argv[2], "%c", &operator) != 1)
	{
		printf("Az elso es a harmadik argumentum, a masodik pedig egy muveleti jel legyen!\n");
		return 1;
	}

	double result;

	switch (operator)
	{
	case '+':
		result = operand1 + operand2;
		break;
	case '-':
		result = operand1 - operand2;
		break;
	case '*':
		result = operand1 * operand2;
		break;
	case '/':
		result = operand1 / operand2;
		break;
	case '^':
		result = pow(operand1, operand2);
		break;
	default:
		printf("A masodik argumentum nem egy muveleti jel.\n");
		return 1;
	}

	printf("Az eredmeny: %f\n", result);

	return 0;
}
