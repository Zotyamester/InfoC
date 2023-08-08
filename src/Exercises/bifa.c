#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include "debugmalloc.h"

#include <stdio.h>
#include <stdlib.h>

typedef struct BiFa
{
	int ertek;
	struct BiFa* bal, * jobb;
} BiFa;

BiFa* beszur(BiFa* gyoker, int ertek)
{
	if (gyoker == NULL)
	{
		gyoker = (BiFa*)malloc(sizeof(BiFa));
		if (gyoker == NULL)
			return NULL;

		gyoker->ertek = ertek;
		gyoker->bal = gyoker->jobb = NULL;
	}
	else if (ertek < gyoker->ertek)
	{
		gyoker->bal = beszur(gyoker->bal, ertek);
	}
	else if (ertek > gyoker->ertek)
	{
		gyoker->jobb = beszur(gyoker->jobb, ertek);
	}

	return gyoker;
}

void felszabadit(BiFa* gyoker)
{
	if (gyoker == NULL)
		return;

	felszabadit(gyoker->bal);
	felszabadit(gyoker->jobb);
	free(gyoker);
}

void kiir(const BiFa* gyoker)
{
	if (gyoker == NULL)
		return;

	kiir(gyoker->bal);
	printf("%d ", gyoker->ertek);
	kiir(gyoker->jobb);
}

void kiir_sor(const BiFa* gyoker)
{
	kiir(gyoker);
	putchar('\n');
}

BiFa** min_keres(BiFa** pgyoker)
{
	if (*pgyoker == NULL)
		return pgyoker;

	while ((*pgyoker)->bal != NULL)
		pgyoker = &(*pgyoker)->bal;
	return pgyoker;
}

void ertek_csere(int* pa, int* pb)
{
	int tmp = *pa;
	*pa = *pb;
	*pb = tmp;
}

BiFa* torol(BiFa* gyoker)
{
	if (gyoker == NULL)
	{
		return NULL;
	}
	else if (gyoker->bal != NULL && gyoker->jobb != NULL)
	{
		BiFa** pmin = min_keres(&gyoker->jobb);
		ertek_csere(&gyoker->ertek, &(*pmin)->ertek);
		*pmin = torol(*pmin);
		return gyoker;
	}
	else if (gyoker->bal == NULL && gyoker->jobb == NULL)
	{
		free(gyoker);
		return NULL;
	}
	else
	{
		BiFa* kov = gyoker->bal == NULL ? gyoker->jobb : gyoker->bal;
		free(gyoker);
		return kov;
	}
}

BiFa* torol_ertek(BiFa* gyoker, int ertek)
{
	if (gyoker == NULL)
		return NULL;

	if (ertek < gyoker->ertek)
		gyoker->bal = torol_ertek(gyoker->bal, ertek);
	else if (ertek > gyoker->ertek)
		gyoker->jobb = torol_ertek(gyoker->jobb, ertek);
	else
		gyoker = torol(gyoker);

	return gyoker;
}

int int_cmp(const void* pa, const void* pb)
{
	int* pia = (const int*)pa;
	int* pib = (const int*)pb;

	if (*pia < *pib)
		return -1;
	return *pia > *pib;
}

int elemek_szama(BiFa* gyoker)
{
	if (gyoker == NULL)
		return 0;

	return 1 + elemek_szama(gyoker->bal) + elemek_szama(gyoker->jobb);
}

int elemek_osszege(BiFa* gyoker)
{
	if (gyoker == NULL)
		return 0;

	return gyoker->ertek + elemek_osszege(gyoker->bal) + elemek_osszege(gyoker->jobb);
}

BiFa* elem_keres(BiFa* gyoker, int elem)
{
	while (gyoker != NULL && gyoker->ertek != elem)
		if (gyoker->ertek > elem)
			gyoker = gyoker->bal;
		else
			gyoker = gyoker->jobb;
	return gyoker;
}

BiFa* elem_keres_rek(BiFa* gyoker, int elem)
{
	if (gyoker == NULL || gyoker->ertek == elem)
		return gyoker;
	else if (gyoker->ertek < elem)
		return elem_keres_rek(gyoker->jobb, elem);
	else
		return elem_keres_rek(gyoker->bal, elem);
}

void negalas(BiFa* gyoker)
{
	if (gyoker == NULL)
		return;

	gyoker->ertek *= -1; /* ezzel szépen el is rontottuk a rendezettséget, a keresõfa tulajdonságot */
	negalas(gyoker->bal);
	negalas(gyoker->jobb);
}

void tukrozes(BiFa* gyoker)
{
	if (gyoker == NULL)
		return;

	BiFa* tmp = gyoker->bal;
	gyoker->bal = gyoker->jobb;
	gyoker->jobb = tmp;

	tukrozes(gyoker->bal);
	tukrozes(gyoker->jobb);
}

bool keresofa_e(BiFa* gyoker)
{
	return  (gyoker == NULL) ||
		(gyoker->bal == NULL || gyoker->bal->ertek < gyoker->ertek && keresofa_e(gyoker->bal)) &&
		(gyoker->jobb == NULL || gyoker->jobb->ertek > gyoker->ertek && keresofa_e(gyoker->jobb));
}

bool ketto_vagy_nulla(BiFa* gyoker)
{
	return  gyoker == NULL ||
		(gyoker->bal == NULL) == (gyoker->jobb == NULL) &&
		ketto_vagy_nulla(gyoker->bal) && ketto_vagy_nulla(gyoker->jobb);
}

int meddig_teljes(BiFa* gyoker)
{
	if (gyoker == NULL)
		return 0;

	int meddig_bal = meddig_teljes(gyoker->bal);
	int meddig_jobb = meddig_teljes(gyoker->jobb);

	return 1 + (meddig_bal <= meddig_jobb ? meddig_bal : meddig_jobb);
}

BiFa* hasonlit(BiFa* bf1, BiFa* bf2)
{
	return  bf1 == NULL && bf2 == NULL ||
		bf1 != NULL && bf2 != NULL &&
		bf1->ertek == bf2->ertek &&
		hasonlit(bf1->bal, bf2->bal) && hasonlit(bf1->jobb, bf2->jobb);
}

BiFa* masol(BiFa* gyoker)
{
	if (gyoker == NULL)
		return NULL;

	BiFa* masolat = (BiFa*)malloc(sizeof(BiFa));
	if (masolat == NULL)
		return NULL;

	masolat->ertek = gyoker->ertek;

	masolat->bal = masol(gyoker->bal);
	masolat->jobb = masol(gyoker->jobb);

	return masolat;
}

int main(int argc, char* argv[])
{
	int tomb[] = { 5, 9, 1, 8, 4, 7, 2, 10, 3, 6 };
	const int n = sizeof(tomb) / sizeof(int);

	BiFa* gyoker = NULL;
	for (int i = 0; i < n; i++)
		gyoker = beszur(gyoker, tomb[i]);

	kiir_sor(gyoker);

	//qsort(tomb, n, sizeof(int), int_cmp);

	for (int i = 0; i < n; i++)
	{
		gyoker = torol_ertek(gyoker, tomb[i]);
		kiir_sor(gyoker);
	}

	felszabadit(gyoker);

	return 0;
}
