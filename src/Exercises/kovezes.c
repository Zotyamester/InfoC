#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

/// <summary>
/// Ki�rja az �sszes kik�vez�si lehet�s�get.
/// A f�ggv�ny fel�telezi, hogy a <paramref name="kovezes"/> kell�en hossz� ahhoz,
/// hogy m�g a leghosszabb k�vez�si kombin�ci� (�s egy lez�r� nulla) is belef�rjen.
/// </summary>
/// <param name="kovezes">A seg�dt�mb, amiben a f�ggv�ny elt�rolja a k�vez�si kombin�ci�t</param>
/// <param name="jelenlegi">Ahonnan fel lehet t�lteni a <paramref name="kovezes"/>-t, alap�rtelmezetten 0.</param>
/// <param name="hossz">A j�rda hossz�s�ga</param>
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
