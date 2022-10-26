#include <stdio.h>
#include <stdbool.h>

void csere(int* pa, int* pb)
{
	int temp = *pa;
	*pa = *pb;
	*pb = temp;
}

void buborekrendezes(int* tomb, int meret)
{
	for (int vege = meret - 1; vege > 0; vege--)
	{
		bool volt_csere = false;

		for (int i = 0; i < vege; i++)
		{
			if (tomb[i] > tomb[i + 1])
			{
				csere(&tomb[i], &tomb[i + 1]);
				volt_csere = true;
			}
		}

		if (!volt_csere)
			break;
	}
}

void kivalasztasos_rendezes(int* tomb, int meret)
{
	for (int i = 0; i < meret; i++)
	{
		int min = i;

		for (int j = i + 1; j < meret; j++)
		{
			if (tomb[j] < tomb[min])
				min = j;
		}
		
		csere(&tomb[i], &tomb[min]);
	}
}

static void gyorsrendezes_(int* tomb, int elso, int utolso)
{
	int pivot = tomb[(elso + utolso) / 2];
	int eleje = elso, vege = utolso;

	while (eleje <= vege)
	{
		while (tomb[eleje] < pivot)
			eleje++;
		while (tomb[vege] > pivot)
			vege--;
		if (eleje <= vege)
		{
			csere(&tomb[eleje], &tomb[vege]);
			eleje++;
			vege--;
		}
	}

	if (elso < vege)
		gyorsrendezes_(tomb, elso, vege);
	if (eleje < utolso)
		gyorsrendezes_(tomb, eleje, utolso);
}

void gyorsrendezes(int* tomb, int meret)
{
	gyorsrendezes_(tomb, 0, meret - 1);
}

void kertitorpe_rendezes(int* tomb, int meret)
{
	int i = 1;
	while (i < meret)
	{
		if (i == 0 || tomb[i - 1] <= tomb[i])
		{
			i++;
		}
		else
		{
			csere(&tomb[i - 1], &tomb[i]);
			i--;
		}
	}
}

int main(void)
{
	static void (*rendezesek[])(int*, int) = {
		buborekrendezes,
		kivalasztasos_rendezes,
		gyorsrendezes,
		kertitorpe_rendezes
	};

	int tomb[10] = { 3, 5, 1, 9, 4, 8, 6, 7, 2, 10 };

	kertitorpe_rendezes(tomb, 10);
	for (int i = 0; i < 10; i++)
		printf("%d ", tomb[i]);
	printf("\n");

	return 0;
}
