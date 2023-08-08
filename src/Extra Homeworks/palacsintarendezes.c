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
	ListaElem* legnagyobb = lista; /* felt�telezz�k, hogy a lista legal�bb egy elemb�l �ll */

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
 * �gy rendez�nk, hogy a lista eleje legyen a torony teteje,
 * a v�ge pedig a torony alja, �gy kezdetben el�g a lista elej�re
 * mutat� pointert ismern�nk, mert a lista v�ge majd automatikusan
 * ad�dik a m�sodik ford�t�s ut�n (hisz �pp azt akarjuk el�rni,
 * hogy a legnagyobb ker�lj�n oda).
 * 
 * @param lista A rendezni k�v�nt lista elej�re mutat� pointer.
 * @return Az �trendezett lista elej�re mutat� poitner.
 */
ListaElem* lista_palacsintarendezes(ListaElem* lista)
{
	ListaElem* vege = NULL; /* eleinte az eg�sz list�n dolgozunk, azt tekintj�k r�szlist�nak */

	while (vege != lista) /* majd folyamatosan sz�k�l� r�szlist�kon dolgozunk tov�bb */
	{
		ListaElem* legnagyobb = lista_legnagyobb(lista, vege); /* a r�szlist�ban megkeress�k a legnagyobbat */

		lista = lista_fordit(lista, legnagyobb->kov); /* megford�tjuk a list�t a legnagyobbig */
		lista_kiir(lista);

		lista = lista_fordit(lista, vege); /* megford�tjuk a list�t a r�szlista v�g�ig */
		lista_kiir(lista);

		vege = legnagyobb; /* mindig a legnagyobb ker�l a v�g�re; azzal m�r nem kell t�r�dni, sz�k�tj�k a r�szlist�t */
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

	lista_kiir(lista); /* kezdeti �llapot ki�r�sa */
	lista = lista_palacsintarendezes(lista);

	lista_felszabadit(lista);

	return 0;
}
