#include <stdio.h>

typedef enum { false = 0, true = 1 } bool;

bool isspace(char c)
{
	return c == ' ' || c == '\t' || c == '\n' || c == '\v' || c == '\f' || c == '\r';
}

bool isdigit(char c)
{
	return c >= '0' && c <= '9';
}

bool islower(char c)
{
	return c >= 'a' && c <= 'z';
}

bool isupper(char c)
{
	return c >= 'A' && c <= 'Z';
}

int dec_to_int(char* s)
{
	int n = 0;

	while (isspace(*s))
		s++;

	bool negative = false;
	if (*s == '-')
	{
		negative = true;
		s++;
	}

	char c;
	while ((c = *s++) != '\0')
	{
		if (!isdigit(c))
			break; // from now on it's NaN

		n = 10 * n + (c - '0');
	}

	if (negative)
		n *= -1;

	return n;
}

int hexa_to_int(char* s)
{
	int n = 0;

	while (isspace(*s))
		s++;

	bool negative = false;
	if (*s == '-')
	{
		negative = true;
		s++;
	}

	char c;
	while ((c = *s++) != '\0')
	{
		if (isdigit(c))
			c = c - '0';
		else if (islower(c))
			c = c - 'a' + 10;
		else if (isupper(c))
			c = c - 'A' + 10;
		else
			break; // from now on it's NaN

		n = 16 * n + c;
	}

	if (negative)
		n *= -1;

	return n;
}

const char *strstr(const char* str, const char* sub)
{
	int i;
	for (i = 0; str[i] != '\0'; i++)
	{
		int j;
		for (j = 0; sub[j] != '\0' && str[i + j] == sub[j]; j++)
			;
		if (sub[j] == '\0')
			return str + i;
	}
	return NULL;
}

char* strlcat(char* dst, const char* src, size_t n)
{
	size_t i = 0;

	while (dst[i] != '\0')
		i++;

	while (i < n - 1 && *src != '\0')
		dst[i++] = *src++;

	dst[i] = '\0';

	return dst;
}

int main(int argc, char* argv[])
{
	int a = dec_to_int(" -534 ");
	int b = hexa_to_int(" ff14 ");
	printf("%d %X\n", a, b);

	printf("%s in %s starts from %s\n", "abc", "abcdabce", strstr("abcdabce", "abc"));

	char basestr[32] = "alma";
	strlcat(basestr, " ", 32);
	strlcat(basestr, "fucking faaaaaaaaaaa... :)", 32);
	printf("res: %s\n", basestr);

	return 0;
}
