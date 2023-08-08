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

/* Felszabad�t egy dek�dol� f�t. */
void morse_free(Morse* morse)
{
	if (morse == NULL)
		return;

	morse_free(morse->dot);
	morse_free(morse->dash);
	free(morse);
}

/* L�trehoz egy �j elemet (egy dek�dol� f�hoz). */
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

/* L�trehoz egy dek�dol� f�t egy morze�b�c�b�l.*/
Morse* morse_read_from_table(char const* const* encodings)
{
	Morse* base = NULL;

	for (int idx = 0; idx < ALPHABET_LEN; idx++)
	{
		char const* code = encodings[idx]; /* idx. bet� morzek�dja */
		Morse** to = &base; /* pointer oda, ahov� vezet a morzek�d */

		do
		{
			if (*to == NULL) /* utat t�r�nk a k�dol�snak, ahogy megy�nk */
			{
				Morse* node = morse_new_node('\0', NULL, NULL);
				if (node == NULL)
				{
					morse_free(base); /* sikertelen foglal�s eset�n, az eg�sz f�t t�r�lj�k */
					return NULL;
				}

				*to = node;
			}

			if (*code == '.')
				to = &(*to)->dot;
			else if (*code == '-')
				to = &(*to)->dash;
			else
				; /* kommentk�nt �rtj�k az �sszes t�bbi karaktert */
		} while (*code++ != '\0'); /* ha a nulltermin�ntort dolgoztuk fel legut�bb, kil�p�nk */

		(*to)->character = 'A' + (char)idx; /* az utolj�ra feldolgozotthoz rendelj�k a karaktert */
	}

	return base;
}

/* Ki�r n darab tabul�tor karaktert a f�jlba. */
void write_indents(int n, FILE* file)
{
	for (int i = 0; i < n; i++)
		fputc('\t', file);
}

/* Rekurz�van bej�rja dek�dol� fa �sszes �g�t, �s ki�rja
 * az az alapj�n l�trehozott d�nt�si fa el�gaz�sait C-ben
 * megfelel� t�rdel�ssel. A level adja meg a kezd� t�rdel�s
 * m�rt�k�t �s egyben, hogy milyen m�lys�gben van a dek�dol�s,
 * �gy a fa gy�ker�re megh�vva egynek kell lennie. */
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
		if (had_if) /* ki lett �rva egy else az el�z� if-n�l */
			fputc(' ', file);
		else
			write_indents(level, file);
		fprintf(file, "if (s[%d] == '-')\n", level - 1);

		morse_write_branch(morse->dash, level + 1, file);

		write_indents(level, file);
		fprintf(file, "else");
		had_if = true;
	}

	if (had_if) /* ki lett �rva egy else az el�z� if-n�l */
		fprintf(file, "\n\t"); /* k�l�n sorba �s eggyel beljebb */

	write_indents(level, file);
	if (morse->character != '\0')
		fprintf(file, "printf(\"%c\");\n", morse->character);
	else
		fprintf(file, "printf(\"ervenytelen\");\n");
}

/* Ki�rja a decode f�ggv�ny h�v�sait a f�jlba. */
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

/* L�trehoz egy dek�dol� f�t egy ABC-b�l, majd ki�rja a dek�dol� f�t le�r� C
 * programot, amiben dek�dolja az itt kapott sztring morzek�dj�nak dek�doltj�t */
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

/* A f�programban t�roljuk a morze�b�c�t, itt nyitjuk meg al�trehozand� f�jlt,
 * �s ugyanitt kezelj�k le az esetleges hib�kat is. */
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
