#include <stdio.h>
#include <stdbool.h>

typedef enum Allapot {
	alap, per_volt, cpp_komment, c_komment, c_komment_csillag_volt, c_komment_per_volt, literal, literal_fper_volt
} Allapot;

int main(int argc, char *argv[])
{
	Allapot allapot = alap;

	int karakter;
	while ((karakter = getchar()) != EOF)
	{
		switch (allapot)
		{
		case alap:
			if (karakter == '/')
				allapot = per_volt;
			else
			{
				putchar(karakter);
				if (karakter == '"')
					allapot = literal;
			}
			break;
		case per_volt:
			if (karakter == '/')
				allapot = cpp_komment;
			else if (karakter == '*')
				allapot = c_komment;
			else
			{
				putchar('/');
				putchar(karakter);
				allapot = alap;
			}
			break;
		case cpp_komment:
			if (karakter == '\n')
			{
				putchar('\n');
				allapot = alap;
			}
			break;
		case c_komment:
			if (karakter == '*')
				allapot = c_komment_csillag_volt;
			else if (karakter == '/')
				allapot = c_komment_per_volt;
			break;
		case c_komment_csillag_volt:
			if (karakter == '/')
				allapot = alap;
			else if (karakter != '*')
				allapot = c_komment;
			break;
		case c_komment_per_volt:
			if (karakter == '*')
			{
				fprintf(stderr, "Hiba: C-kommentben C-komment.\n");
				return 2;
			}
			else if (karakter != '/')
				allapot = c_komment;
			break;
		case literal:
			putchar(karakter);
			if (karakter == '\\')
				allapot = literal_fper_volt;
			else if (karakter == '"')
				allapot = alap;
			break;
		case literal_fper_volt:
			putchar(karakter);
			allapot = literal;
			break;
		default:
			fprintf(stderr, "Hibas allapot.\n");
			return 3;
		}
	}

	if (allapot != alap)
	{
		fprintf(stderr, "Hibas bemeneti fajl.\n");
		return 1;
	}

	return 0;
}
