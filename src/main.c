#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <string.h>

int jarda(int n, int k)
{
	if (n == 0)
		return 1;

	int max_csempe = (n >= k) ? k : n;
	int db = 0;
	for (int csempe = 1; csempe <= max_csempe; csempe += 1)
		db += jarda(n - csempe, max_csempe);
	return db;
}

//bool benne_van_e(int *tomb, int meret, int elem)
//{
//	for (int i = 0; i < meret; i++)
//	{
//		if (tomb[i] == elem)
//		{
//			return true;
//		}
//	}
//	return false;
//}

/// más

//void kiir_egyesek(int szam)
//{
//	int egyesek = szam % 10;
//
//	switch (egyesek)
//	{
//	case 0:
//		if (szam == 0) // csak ha az egész szám nulla, akkor kell kiírni
//			printf("nulla");
//		break;
//	case 1:
//		printf("egy");
//		break;
//	case 2:
//		printf("ketto");
//		break;
//	case 3:
//		printf("harom");
//		break;
//	case 4:
//		printf("negy");
//		break;
//	case 5:
//		printf("ot");
//		break;
//	case 6:
//		printf("hat");
//		break;
//	case 7:
//		printf("het");
//		break;
//	case 8:
//		printf("nyolc");
//		break;
//	case 9:
//		printf("kilenc");
//		break;
//	default:
//		break;
//	}
//}
//
//void kiir_tizesek(int szam)
//{
//	int egyesek = szam % 10;
//	int tizesek = (szam / 10) % 10;
//
//	switch (tizesek)
//	{
//	case 1:
//		printf("tiz");
//		if (egyesek > 0)
//			printf("en");
//		break;
//	case 2:
//		printf("husz");
//		if (egyesek > 0)
//			printf("on");
//		break;
//	case 3:
//		printf("harminc");
//		break;
//	case 4:
//	case 5:
//	case 7:
//	case 9:
//		kiir_egyesek(tizesek);
//		printf("ven");
//		break;
//	case 6:
//	case 8:
//		kiir_egyesek(tizesek);
//		printf("van");
//		break;
//	default:
//		break;
//	}
//}
//
//void kiir_szazasok(int szam)
//{
//	int szazasok = (szam / 100) % 10;
//
//	switch (szazasok)
//	{
//	case 1:
//		if (szam < 1000)
//			break;
//	default:
//		kiir_egyesek(szazasok);
//		break;
//	}
//	printf("szaz");
//}
//
//void kiir_ezresek(int szam)
//{
//	int ezresek = (szam / 1000) % 10;
//
//	switch (ezresek)
//	{
//	case 1:
//		if (szam < 10000)
//			break;
//	default:
//		kiir_egyesek(ezresek);
//		break;
//	}
//	printf("ezer");
//}
//
//void kiir_szam(int szam)
//{
//	kiir_ezresek(szam);
//	if (szam > 2000)
//		printf("-");
//	kiir_szazasok(szam);
//	kiir_tizesek(szam);
//	kiir_egyesek(szam);
//}

/// más

//int hany_szamjegyu(int szam)
//{
//	int jegyek = 0;
//
//	do
//	{
//		jegyek += 1;
//		szam /= 10;
//	} while (szam != 0);
//
//	return jegyek;
//}
//
//int hatvanyoz(int a, int n)
//{
//	if (a == 1 || n == 0)
//	{
//		return 1;
//	}
//
//	if (n % 2 == 0)
//	{
//		return hatvanyoz(a * a, n / 2);
//	}
//
//	return a * hatvanyoz(a, n - 1);
//}
//
//bool armstrong_e(int szam)
//{
//	int szumma = 0;
//
//	int n = hany_szamjegyu(szam);
//	for (int x = szam; x > 0; x /= 10)
//	{
//		int jegy = x % 10;
//		szumma += hatvanyoz(jegy, n);
//	}
//
//	return szumma == szam;
//}

/// más

//int osztok_szama(int szam)
//{
//	int osztok = 1;
//	for (int oszto = 1; oszto <= szam; oszto++)
//		if (szam % oszto == 0)
//			osztok++;
//	return osztok;
//}
//
//bool van_benne_hetes(int szam)
//{
//	while (szam > 0)
//	{
//		if (szam % 10 == 7)
//			return true;
//		szam /= 10;
//	}
//	return false;
//}

/// más

//void _kiir_binaris(unsigned n)
//{
//	if (n == 0)
//	{
//		printf("0");
//	}
//	else
//	{
//		if (n / 2 > 0)
//			_kiir_binaris(n / 2);
//		printf("%d", n % 2);
//	}
//}
//
//void kiir_binaris(unsigned n)
//{
//	_kiir_binaris(n);
//	printf("\n");
//}
//
//unsigned bitset(unsigned n, unsigned bit)
//{
//	return n | (1 << bit);
//}
//
//unsigned bitreset(unsigned n, unsigned bit)
//{
//	return n & ~(1 << bit);
//}
//
//unsigned bitnegate(unsigned n, unsigned bit)
//{
//	return n ^ (1 << bit);
//}

/// más

//int scan_for_radix(unsigned int* radix)
//{
//	if (scanf("%u", radix) != 1)
//		return 1;
//	if (*radix < 2 || *radix > 36)
//		return 2;
//	return 0;
//}
//
//unsigned long todecimal(char* digits, unsigned int radix)
//{
//	unsigned long decimal = 0;
//
//	char c;
//	while ((c = *digits++) != '\0')
//	{
//		unsigned int digit_to_add;
//
//		if (c >= '0' && c <= '9')
//			digit_to_add = c - '0';
//		else if (c >= 'a' && c <= 'z')
//			digit_to_add = c - 'a' + 10; // a=10,b=11,...,z=35
//		else if (c >= 'A' && c <= 'Z')
//			digit_to_add = c - 'A' + 10; // A=10,B=11,...,Z=35
//		else
//			continue; // NaN => Not a Number
//
//		decimal = decimal * radix + digit_to_add;
//	}
//
//	return decimal;
//}
//
//void fromdecimal(unsigned long number, unsigned int radix, char* digits)
//{
//	if (number == 0)
//	{
//		digits[0] = '0';
//		digits[1] = '\0';
//	}
//	else
//	{
//		unsigned int end = 0;
//
//		while (number > 0)
//		{
//			unsigned int digit = number % radix;
//			digits[end++] = (digit < 10) ? (digit + '0') : (digit - 10 + 'A');
//			number /= radix;
//		}
//		digits[end] = '\0';
//
//		end--; // step back to the last digit
//		unsigned int start = 0;
//
//		// reverse the digits, since they were written in Least Significant Byte first or Little Endian
//		while (start < end)
//		{
//			char temp = digits[start];
//			digits[start] = digits[end];
//			digits[end] = temp;
//
//			start++;
//			end--;
//		}
//	}
//}

/// más

//void trim_by_x(char *dst, const char *src, char x)
//{
//	while (*src == x)
//		src++;
//	while (*src != '\0')
//		*dst++ = *src++;
//	*dst = x;
//	while(*dst == x)
//		dst--;
//	*++dst = '\0';
//}
//
//void trim(char *dst, const char *src)
//{
//	trim_by_x(dst, src, ' ');
//}

/// más

//void caesar_kodolas(char *dst, const char *src, int offset)
//{
//	while (*src)
//	{
//		char c = *src;
//		if (c >= 'a' && c <= 'z')
//			c = ((c - 'a') + offset) % 26 + 'a';
//		*dst = c;
//		dst++, src++;
//	}
//	*dst = '\0';
//}

/// más

//const char *strptr_without_prefix(const char *s, const char *prefix)
//{
//	while (*s == *prefix)
//	{
//		s++;
//		prefix++;
//	}
//
//	return s;
//}
//
//int strcmp_the(const char *s1, const char *s2)
//{
//	s1 = strptr_without_prefix(s1, "The ");
//	s2 = strptr_without_prefix(s2, "The ");
//
//	// return strcmp(s1, s2); ?
//	while (*s1)
//	{
//		if (*s1 < *s2)
//			return -1;
//		else if (*s1 > *s2)
//			return 1;
//		s1++, s2++;
//	}
//
//	return 0;
//}

/// más

//unsigned int ip_cim(const char* str)
//{
//	unsigned int a, b, c, d;
//	if (sscanf(str, "%u.%u.%u.%u", &a, &b, &c, &d) == 4
//		&& a >= 0 && a <= 255
//		&& b >= 0 && b <= 255
//		&& c >= 0 && c <= 255
//		&& d >= 0 && d <= 255)
//		return (a << 24) | (b << 16) | (c << 8) | d;
//	return ~0; // on error: arbitrary big number => 2^32 - 1
//}
//
//unsigned int ip_cim_fast(const char* str)
//{
//	unsigned int ip = 0;
//	unsigned char acc = 0;
//	char c;
//	while ((c = *str++) != '\0')
//	{
//		if (c >= '0' && c <= '9')
//			acc = acc * 10 + c - '0';
//		else if (c == '.')
//			ip = ip << 8 | acc; // + acc would make it too
//	}
//	ip = ip << 8 | acc; // the last one didn't make it to the ip 'til now
//	return ip; // note that it does not check the validity of the ip address, it might just let the bytes overflow
//}

/// más

//char* _readline(size_t size)
//{
//	char* line;
//
//	int c = getchar();
//	if (c == '\n' || c == EOF)
//	{
//		line = (char*)malloc((size + 1) * sizeof(char));
//		c = '\0';
//	}
//	else
//	{
//		line = _readline(size + 1);
//	}
//
//	if (line != NULL)
//		line[size] = c;
//
//	return line;
//}
//
//char* readline()
//{
//	return _readline(0);
//}

/// más

/*void print_in_base_r(unsigned n, unsigned r)
{
	if (n == 0)
		return;
	print_in_base_r(n / r, r);
	unsigned digit = n % r;
	putchar((digit < 10) ? ('0' + digit) : ('A' + digit - 10));
}*/

/// más

/*/// <summary>
/// Szétválogatja a tömb elemeit paritásuk szerint, így a párosak kerülnek előre, a páratlanok pedig hátra.
/// </summary>
/// <param name="tomb">a tömb</param>
/// <param name="meret">a tömb mérete</param>
void szetvalogat(int* tomb, int meret)
{
	int elso = 0, utolso = meret - 1;
	while (elso < utolso)
	{
		while (elso < utolso && tomb[utolso] % 2 != 0) utolso--; // a végéről keresünk párost
		while (elso < utolso && tomb[elso] % 2 == 0) elso++; // az elejéről keresünk páratlant
		if (elso < utolso)
		{
			int temp = tomb[elso];
			tomb[elso] = tomb[utolso];
			tomb[utolso] = temp;

			// ez igazából már lényegtelen, egy-egy kört lehet vele spórolni a fenti két ciklusnál 
			elso++;
			utolso--;
		}
	}
}*/

/// más

/*void sztring_fordit(char* sz)
{
	int elso = 0, utolso = 0;
	while (sz[utolso] != '\0') utolso++;
	utolso--;

	while (elso < utolso)
	{
		char tmp = sz[elso];
		sz[elso] = sz[utolso];
		sz[utolso] = tmp;

		elso++;
		utolso--;
	}
}

void szokoztelenit(char* src)
{
	char* dst = src;
	while (*src)
	{
		if (*src != ' ')
			*dst++ = *src;
		src++;
	}
	*dst = '\0';
}

bool palindrom_e1(char* s)
{
	int n = strlen(s);

	for (int i = 0; i < n / 2; i++)
		if (s[i] != s[n - 1 - i])
			return false;

	return true;
}*/


int main()
{
	/*int also, felso;

	scanf("%d %d", &also, &felso);

	also += 10 - also % 10;
	felso -= felso % 10;

	int osszeg = 0;
	if (also <= felso) {
		osszeg = (also + felso) * ((felso - also) / 10 + 1) / 2;
	}

	printf("%d\n", osszeg);*/

	/// más

	/*int a, b;
	printf("a=");
	scanf("%d", &a);
	printf("b=");
	scanf("%d", &b);

	if (a > b) {
		int temp = a;
		a = b;
		b = temp;
	}

	a = a - (a % 2) + 1; // min{n | 2|n, n>=a}

	while (a <= b) {
		printf("%d ", a);
		a += 2;
	}
	printf("\n");*/

	/// más

	/*srand(time(NULL));

	int szam = rand() % 100 + 1;

	int tipp;
	while (printf("Tipp? ") > 0 && scanf("%d", &tipp) == 1 && tipp != szam)
		if (tipp < szam)
			printf("Nagyobb.\n");
		else
			printf("Kisebb.\n");
	printf("Eltalaltad.\n");*/

	/// más

	/*int also = 1, felso = 100;
	char valasz;
	do
	{
		int tipp = (also + felso) / 2;
		printf("Tipp: %d\nKisebb, nagyobb vagy egyenlo (k/n/e)? ", tipp);

		scanf(" %c", &valasz);
		if (valasz == 'k')
		{
			felso = tipp - 1;
		}
		else if (valasz == 'n')
		{
			also = tipp + 1;
		}
	}
	while (valasz != 'e');
	printf("Nagyszeru! Ezek szerint eltalaltam.\n");*/

	/// más

	/*srand(time(NULL));

	int szamok[100];

	for (int i = 0; i < 100; i++)
	{
		int szam;
		do
		{
			szam = rand() % 100 + 1;
		}
		while (benne_van_e(szamok, i, szam));
		szamok[i] = szam;
	}

	// ...

	for (int i = 0; i < 100; i++)
	{
		printf("%d ", szamok[i]);
	}
	printf("\n");*/

	/// más

	/*int szam;

	printf("n=");
	scanf("%d", &szam);

	szam %= 10000; // csak 1-tõl 9999-ig lehetnek, ha nagyobbat kapnánk, redukáljuk százig

	printf("szam: ");
	kiir_szam(szam);
	printf("\n");*/

	/// más

	/*int n;
	if (scanf("%d", &n) == 1)
		printf("%s\n", armstrong_e(n) ? "igen" : "nem");*/

	/// más

	/*int ev = 2016;
	while (osztok_szama(ev) != 8 || !van_benne_hetes(ev))
		ev--;
	printf("ev=%d\n", ev);*/

	/// más

	/*unsigned n = 15;
	kiir_binaris(n); // 1111
	n = bitreset(n, 2);
	kiir_binaris(n); // 1011
	n = bitnegate(n, 1);
	kiir_binaris(n); // 1001
	n = bitset(n, 2);
	kiir_binaris(n); // 1101*/

	/// más

	/*int err;

	unsigned int from_radix;
	printf("Enter the source base's radix:\n");
	if ((err = scan_for_radix(&from_radix)) != 0)
	{
		printf("Invalid radix.\n");
		return err;
	}

	unsigned int to_radix;
	printf("Enter the target base's radix:\n");
	if ((err = scan_for_radix(&to_radix)) != 0)
	{
		printf("Invalid radix.\n");
		return err;
	}

	char digits[64 + 1]; // the lowest is base 2, the biggest number that we can hold in an unsigned long is 64-bit wide
	printf("Enter the number in base %d:\n", from_radix);
	if (scanf("%s", digits) != 1)
	{
		printf("Invalid number.\n");
		return 1;
	}

	unsigned long number = todecimal(digits, from_radix);
	fromdecimal(number, to_radix, digits); // reusing the string/array that used to store the input

	printf("The number in base %d:\n%s\n", to_radix, digits);*/

	/// más

	/*char szoveg[127 + 1] = "  asd lol xd   ";
	char trimmelt[127 + 1];
	trim(trimmelt, szoveg);
	printf("Elotte:\n|%s|\nUtana:\n|%s|\n", szoveg, trimmelt);*/

	/// más

	/*char kodolando[127 + 1], kodolt[127 + 1];
	int offset;
	printf("offset=");
	scanf("%d", &offset);
	printf("text=");
	scanf(" %[^\n]", kodolando);
	caesar_kodolas(kodolt, kodolando, offset);
	printf("encoded=%s\n", kodolt);*/

	/// más

	/*printf("%d %d\n", strcmp("asd", "abba"), strcmp_the("asd", "The abba"));*/

	/// más

	/*printf("%x\n", ip_cim_fast("192.168.1.1"));*/

	/// más

	/*printf("Enter your name: ");
	char* str = readline();
	printf("Your name is %s.\n", str);
	free(str);*/

	/// más

	/*unsigned n, r;
	scanf("%u %u", &n, &r);
	print_in_base_r(n, r);
	putchar('\n');*/

	/// más

	/*int tomb[10] = { 3, 1, 5, 8, 2, 9, 4, 6, 7, 10 };

	szetvalogat(tomb, 10);
	for (int i = 0; i < 10; i++)
		printf("%d ", tomb[i]);
	printf("\n");*/

	/// más

	/*char szoveg[] = "abba mam abba";
	puts(szoveg);
	szokoztelenit2(szoveg);
	puts(szoveg);
	sztring_fordit(szoveg);
	puts(szoveg);
	puts(palindrom_e2(szoveg) ? "igen" : "nem");*/

	for (int i = 0; i <= 4; i++)
		printf("jarda(%d)=%d\n", i, jarda(i, 3));

	return 0;
}
