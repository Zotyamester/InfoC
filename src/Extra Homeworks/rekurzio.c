#include <stdio.h>
#include <stdlib.h>

/* A f�ggv�ny beolvas egy teljes sort (enterig vagy f�jl v�ge jelig) a szabv�nyos
 * bemenetr�l, �s visszaadja egy dinamikusan foglalt sztringben. A sztring
 * null�val van lez�rva, az entert nem tartalmazza. A h�v� felel�ss�ge
 * a free()-t megh�vni a kapott pointerre. */
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
		ch = '\0'; /* ezzel z�rjuk a sztringet, ha sikeres volt a malloc */
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
