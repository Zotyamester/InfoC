#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>

#define ALPHABET_LEN 26

typedef struct morse_struct
{
	char character;
	struct morse_struct* dot, * dash;
} Morse;

/* Felszabadít egy dekódoló fát. */
void morse_free(Morse* morse)
{
	if (morse == NULL)
		return;

	morse_free(morse->dot);
	morse_free(morse->dash);
	free(morse);
}

/* Létrehoz egy új elemet (egy dekódoló fához). */
Morse* morse_new_node(char character, Morse* dot, Morse* dash)
{
	Morse* node = (Morse*)malloc(sizeof(Morse));
	if (node == NULL)
		return NULL;

	node->character = character;
	node->dot = dot;
	node->dash = dash;

	return node;
}

/* Létrehoz egy dekódoló fát egy morzeábécébõl.*/
Morse* morse_read_from_table(char const* const* encodings)
{
	Morse* base = NULL;

	for (int idx = 0; idx < ALPHABET_LEN; idx++)
	{
		char const* code = encodings[idx]; /* idx. betû morzekódja */
		Morse** to = &base; /* pointer oda, ahová vezet a morzekód */

		do
		{
			if (*to == NULL) /* utat törünk a kódolásnak, ahogy megyünk */
			{
				Morse* node = morse_new_node('\0', NULL, NULL);
				if (node == NULL)
				{
					morse_free(base); /* sikertelen foglalás esetén, az egész fát töröljük */
					return NULL;
				}

				*to = node;
			}

			if (*code == '.')
				to = &(*to)->dot;
			else if (*code == '-')
				to = &(*to)->dash;
			else
				; /* kommentként értjük az összes többi karaktert */
		} while (*code++ != '\0'); /* ha a nullterminántort dolgoztuk fel legutóbb, kilépünk */

		(*to)->character = 'A' + (char)idx; /* az utoljára feldolgozotthoz rendeljük a karaktert */
	}

	return base;
}

/* Kiír n darab tabulátor karaktert a fájlba. */
void write_indents(int n, FILE* file)
{
	for (int i = 0; i < n; i++)
		fputc('\t', file);
}

/* Rekurzívan bejárja dekódoló fa összes ágát, és kiírja
 * az az alapján létrehozott döntési fa elágazásait C-ben
 * megfelelõ tördeléssel. A level adja meg a kezdõ tördelés
 * mértékét és egyben, hogy milyen mélységben van a dekódolás,
 * így a fa gyökerére meghívva egynek kell lennie. */
void morse_write_branch(Morse* morse, int level, FILE* file)
{
	bool had_if = false;

	if (morse->dot != NULL)
	{
		write_indents(level, file);
		fprintf(file, "if (s[%d] == '.')\n", level - 1);

		morse_write_branch(morse->dot, level + 1, file);

		write_indents(level, file);
		fprintf(file, "else");
		had_if = true;
	}

	if (morse->dash != NULL)
	{
		if (had_if) /* ki lett írva egy else az elõzõ if-nél */
			fputc(' ', file);
		else
			write_indents(level, file);
		fprintf(file, "if (s[%d] == '-')\n", level - 1);

		morse_write_branch(morse->dash, level + 1, file);

		write_indents(level, file);
		fprintf(file, "else");
		had_if = true;
	}

	if (had_if) /* ki lett írva egy else az elõzõ if-nél */
		fprintf(file, "\n\t"); /* külön sorba és eggyel beljebb */

	write_indents(level, file);
	if (morse->character != '\0')
		fprintf(file, "printf(\"%c\");\n", morse->character);
	else
		fprintf(file, "printf(\"ervenytelen\");\n");
}

/* Kiírja a decode függvény hívásait a fájlba. */
void morse_write_from_string(char const* s, char const* const* encodings, int level, FILE* file)
{
	int c;
	while ((c = *s++) != '\0')
	{
		if (isalpha(c))
		{
			c = toupper(c);

			write_indents(level, file);
			fprintf(file, "decode(\"%s\");\n", encodings[c - 'A']);
		}
	}
}

/* Létrehoz egy dekódoló fát egy ABC-bõl, majd kiírja a dekódoló fát leíró C
 * programot, amiben dekódolja az itt kapott sztring morzekódjának dekódoltját */
bool morse_write_decoder(char const* s, char const* const* encodings, FILE* file)
{
	Morse* morse = morse_read_from_table(encodings);
	if (morse == NULL)
		return false;

	fprintf(
		file,
		"#include <stdio.h>\n"
		"\n"
		"void decode(const char* s)\n"
		"{\n"
	);

	if (morse != NULL)
		morse_write_branch(morse, 1, file);

	fprintf(
		file,
		"}\n\n"
		"int main(void)\n"
		"{\n"
	);

	morse_write_from_string(s, encodings, 1, file);

	fprintf(file,
		"\treturn 0;\n"
		"}\n"
	);

	morse_free(morse);

	return true;
}

/* A fõprogramban tároljuk a morzeábécét, itt nyitjuk meg alétrehozandó fájlt,
 * és ugyanitt kezeljük le az esetleges hibákat is. */
int main(void)
{
	char const* morse_table[ALPHABET_LEN] = {
		".-", "-...", "-.-.", "-..", ".", "..-.", "--.", "....", "..", ".---",
		"-.-", ".-..", "--", "-.", "---", ".--.", "--.-", ".-.", "...", "-",
		"..-", "...-", ".--", "-..-", "-.--", "--.."
	};

	FILE* file = fopen("morzedekoder.c", "w");
	if (file == NULL)
	{
		perror("Nem sikerult megnyitni a fajlt");
		return 1;
	}

	if (!morse_write_decoder("Zoltan", morse_table, file))
	{
		perror("Nem sikerult a foglalas");
		fclose(file);
		return 2;
	}

	fclose(file);

	return 0;
}
