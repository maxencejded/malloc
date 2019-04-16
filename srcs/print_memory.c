#include "malloc.h"

static void		putnbr_hex(int octet)
{
	static char	*base = "0123456789abcdef";

	write(1, base + (octet >> 4) % 16, 1);
	write(1, base + octet % 16, 1);
}

static void		putchar_hex(unsigned char *ptr, int j)
{

	while (j >= 0)
	{
		if (32 <= *(ptr - j) && *(ptr - j) <= 126)
			write(1, ptr - j, 1);
		else
			write(1, ".", 1);
		j -= 1;
	}
	write(1, "\n", 1);
}

void			print_memory(void *addr, size_t size)
{
	int				j;
	int				k;
	size_t			i;
	unsigned char	*ptr;

	ptr = addr;
	i = 0;
	j = 0;
	while (i < size)
	{
		putnbr_hex(*(ptr + i));
		(i % 2) ? write(1, " ", 1) : 0;
		(j == 15) ? putchar_hex(ptr + i, j) : 0;
		j = (j == 15) ? 0 : j + 1;
		i += 1;
	}
	if (j != 0)
	{
		k = -1;
		while (++k + j < 16)
			((k + j) % 2) ? write(1, "   ", 3) : write(1, "  ", 2);
		putchar_hex(ptr + i, j - 1);
	}
}
