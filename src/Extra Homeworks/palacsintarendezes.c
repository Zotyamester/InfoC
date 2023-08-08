#include <stdio.h>
#include <stdlib.h>

typedef struct ListaElem
{
	int szam;
	struct ListaElem* kov;
} ListaElem;

void lista_felszabadit(ListaElem* fej)
{
	while (fej != NULL)
	{
		ListaElem* kov = fej->kov;
		free(fej);
		fej = kov;
	}
}

ListaElem* lista_tombbol(const int* tomb, int meret)
{
	ListaElem* fej = NULL;

	for (int i = meret - 1; i >= 0; i--)
	{
		ListaElem* elem = (ListaElem*)malloc(sizeof(ListaElem));
		if (elem == NULL)
		{
			lista_felszabadit(fej);
			return NULL;
		}

		elem->szam = tomb[i];
		elem->kov = fej;
		fej = elem;
	}

	return fej;
}

void lista_kiir(ListaElem* fej)
{
	while (fej != NULL)
	{
		printf("%d ", fej->szam);
		fej = fej->kov;
	}
	printf("\n");
}

ListaElem* lista_legnagyobb(ListaElem* lista, ListaElem* stop)
{
	ListaElem* legnagyobb = lista; /* feltételezzük, hogy a lista legalább egy elembõl áll */

	for (ListaElem* mozgo = lista->kov; mozgo != stop; mozgo = mozgo->kov)
		if (mozgo->szam > legnagyobb->szam)
			legnagyobb = mozgo;

	return legnagyobb;
}

ListaElem* lista_fordit(ListaElem* lista, ListaElem* stop)
{
	ListaElem* eleje = stop;

	ListaElem* mozgo = lista;
	while (mozgo != stop)
	{
		ListaElem* kov = mozgo->kov;

		mozgo->kov = eleje;
		eleje = mozgo;

		mozgo = kov;
	}

	return eleje;
}

/**
 * Úgy rendezünk, hogy a lista eleje legyen a torony teteje,
 * a vége pedig a torony alja, így kezdetben elég a lista elejére
 * mutató pointert ismernünk, mert a lista vége majd automatikusan
 * adódik a második fordítás után (hisz épp azt akarjuk elérni,
 * hogy a legnagyobb kerüljön oda).
 * 
 * @param lista A rendezni kívánt lista elejére mutató pointer.
 * @return Az átrendezett lista elejére mutató poitner.
 */
ListaElem* lista_palacsintarendezes(ListaElem* lista)
{
	ListaElem* vege = NULL; /* eleinte az egész listán dolgozunk, azt tekintjük részlistának */

	while (vege != lista) /* majd folyamatosan szûkülõ részlistákon dolgozunk tovább */
	{
		ListaElem* legnagyobb = lista_legnagyobb(lista, vege); /* a részlistában megkeressük a legnagyobbat */

		lista = lista_fordit(lista, legnagyobb->kov); /* megfordítjuk a listát a legnagyobbig */
		lista_kiir(lista);

		lista = lista_fordit(lista, vege); /* megfordítjuk a listát a részlista végéig */
		lista_kiir(lista);

		vege = legnagyobb; /* mindig a legnagyobb kerül a végére; azzal már nem kell törõdni, szûkítjük a részlistát */
	}

	return lista;
}

int main(void)
{
	const int tomb[10] = { 3, 1, 2, 4, 6, 7, 5, 9, 8, 10 };

	ListaElem* lista = lista_tombbol(tomb, sizeof(tomb) / sizeof(int));
	if (lista == NULL)
	{
		perror("Hiba a lista inicializalasa kozben");
		return 1;
	}

	lista_kiir(lista); /* kezdeti állapot kiírása */
	lista = lista_palacsintarendezes(lista);

	lista_felszabadit(lista);

	return 0;
}
