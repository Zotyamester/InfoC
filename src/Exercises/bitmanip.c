#include <stdio.h>
#include <stdint.h>

unsigned extract_bits(unsigned num, unsigned p, unsigned n)
{
	return (num >> (p - 1)) & ((1 << n) - 1);
}

unsigned extbits2(unsigned x, unsigned p, unsigned n)
{
	return (x << (32 - (n + p - 1))) >> (32 - n);
}

uint64_t mirrorn(uint64_t x, uint8_t n)
{
	uint64_t y = 0;
	for (uint8_t i = 0; i < n; i++)
		y |= (((x >> i) & 1) << (n - 1 - i)) | (((x >> (n - 1 - i)) & 1) << i);
	return y;
}

uint32_t subinv(uint32_t x, uint8_t p, uint8_t n)
{
	return x ^ (((1 << n) - 1) << p);
}

uint32_t adjswap(uint32_t x)
{
	uint32_t y = 0;
	for (int pos = 30; pos >= 0; pos -= 2)
	{
		y = (y << 2) | (((x >> pos) & 1) << 1) | ((x >> (pos + 1)) & 1);
	}
	return y;
}

void prttyprntbin(uint32_t x)
{
	uint32_t next_x = x >> 1;
	if (next_x)
		prttyprntbin(next_x);
	putchar('0' + (x & 1));
}

void prntu32(uint32_t x)
{
	for (int pos = 31; pos >= 0; pos--)
		putchar('0' + ((x >> pos) & 1));
}

uint32_t getbin()
{
	uint32_t x = 0;

	int c;
	while ((c = getchar()) == '0' || c == '1')
		x = x << 1 | (c - '0');

	return x;
}

#ifndef _WIN64
uint32_t ror(uint32_t x, uint8_t y)
{
	__asm mov eax, x;
	__asm mov cl, y;
	__asm ror eax, cl;
	__asm mov x, eax;
	return x;
}
#else
uint32_t ror(uint32_t x, uint8_t y)
{
	return (x << (32 - y)) | (x >> y);
}
#endif

inline swap_bytes(uint32_t i)
{
	return (i & 0xFF) << 24 | ((i >> 8) & 0xFF) << 16 | ((i >> 16) & 0xFF) << 8 | ((i >> 24) & 0xFF);
}
int main()
{
	uint32_t i = getbin();
	i = ror(i, 4);
	prntu32(i);

	return 0;
}
