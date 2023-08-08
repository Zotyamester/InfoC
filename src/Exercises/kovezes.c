#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

/// <summary>
/// Kiírja az összes kikövezési lehetõséget.
/// A függvény felételezi, hogy a <paramref name="kovezes"/> kellõen hosszú ahhoz,
/// hogy még a leghosszabb kövezési kombináció (és egy lezáró nulla) is beleférjen.
/// </summary>
/// <param name="kovezes">A segédtömb, amiben a függvény eltárolja a kövezési kombinációt</param>
/// <param name="jelenlegi">Ahonnan fel lehet tölteni a <paramref name="kovezes"/>-t, alapértelmezetten 0.</param>
/// <param name="hossz">A járda hosszúsága</param>
void jarda(char* kovezes, int jelenlegi, int hossz)
{
	if (hossz == 0)
	{
		kovezes[jelenlegi] = '\0';
		puts(kovezes);
	}
	else if (hossz > 0)
	{
		kovezes[jelenlegi] = '-';
		jarda(kovezes, jelenlegi + 1, hossz - 1);
		kovezes[jelenlegi] = '=';
		jarda(kovezes, jelenlegi + 1, hossz - 2);
	}
}

int main(int argc, char* argv[])
{
	int hossz;
	printf("jarda hossza=");
	if (scanf("%d", &hossz) != 1)
	{
		fprintf(stderr, "Nem sikerult beolvasni a jarda hosszusagat.\n");
		return 1;
	}

	if (hossz < 0 || hossz == INT_MAX)
	{
		fprintf(stderr, "Nem megfelelo jarda hosszusag.\n");
		return 2;
	}

	char* kovezes = (char*)malloc((hossz + 1) * sizeof(char));
	if (kovezes == NULL)
	{
		perror("Oh, jaj");
		return 3;
	}

	jarda(kovezes, 0, hossz);

	free(kovezes);
	return 0;
}
