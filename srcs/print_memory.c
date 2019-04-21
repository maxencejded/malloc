/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_memory.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjacques <mjacques@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/20 17:25:31 by mjacques          #+#    #+#             */
/*   Updated: 2019/04/20 17:37:08 by mjacques         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

void			putnbr_hex(int fd, size_t nbr, int size)
{
	static char	*base = "0123456789abcdef";

	if (size > 1)
		putnbr_hex(fd, nbr >> 4, size - 1);
	write(fd, base + (nbr % 16), 1);
}

static void		putchar_mem(unsigned char *ptr, int j)
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
		putnbr_hex(1, *(ptr + i), 2);
		(i % 2) ? write(1, " ", 1) : 0;
		(j == 15) ? putchar_mem(ptr + i, j) : 0;
		j = (j == 15) ? 0 : j + 1;
		i += 1;
	}
	if (j != 0)
	{
		k = -1;
		while (++k + j < 16)
			((k + j) % 2) ? write(1, "   ", 3) : write(1, "  ", 2);
		putchar_mem(ptr + i, j - 1);
	}
}

static void		print_zone(t_malloc *addr)
{
	if (addr)
	{
		print_memory(addr, addr->size);
		print_zone(addr->next);
	}
}

void			malloc_print(void)
{
	print_zone(g_malloc[0]);
	print_zone(g_malloc[1]);
	print_zone(g_malloc[2]);
}
