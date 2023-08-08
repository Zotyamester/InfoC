#include <stdio.h>
#include <stdlib.h>

/* A függvény beolvas egy teljes sort (enterig vagy fájl vége jelig) a szabványos
 * bemenetrõl, és visszaadja egy dinamikusan foglalt sztringben. A sztring
 * nullával van lezárva, az entert nem tartalmazza. A hívó felelõssége
 * a free()-t meghívni a kapott pointerre. */
char* sort_beolvas(void);

int main(void)
{
	char* sor = sort_beolvas();
	if (sor != NULL)
	{
		printf("%s\n", sor);
		free(sor);
	}
	else
	{
		perror("Nem jartam szerencsevel");
	}

	return 0;
}

static char* sort_beolvas_seged(int idx)
{
	char* str;

	int ch = getchar();
	if (ch == EOF || ch == '\n')
	{
		str = (char*)malloc((idx + 1) * sizeof(char));
		ch = '\0'; /* ezzel zárjuk a sztringet, ha sikeres volt a malloc */
	}
	else
	{
		str = sort_beolvas_seged(idx + 1);
	}

	if (str == NULL)
		return NULL;

	str[idx] = ch;

	return str;
}

char* sort_beolvas(void)
{
	return sort_beolvas_seged(0);
}
