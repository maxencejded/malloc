/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_memory.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjacques <mjacques@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/20 17:25:31 by mjacques          #+#    #+#             */
/*   Updated: 2019/09/17 19:45:35 by mjacques         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

void			putnbr_hex(int fd, size_t nbr, size_t size)
{
	static const char	base[] = "0123456789abcdef";

	if (size > 1)
		putnbr_hex(fd, nbr >> 4, size - 1);
	write(fd, base + (nbr & 0xF), 1);
}

static void		putstr_format(unsigned char *ptr, size_t j)
{
	size_t	i;
	char	format[17];

	i = 0;
	format[j + 1] = '\n';
	while (i <= j)
	{
		if (20 <= *(ptr + i) && *(ptr + i) <= 126)
			format[i] = *(ptr + i);
		else
			format[i] = '.';
		++i;
	}
	write(STDOUT_FILENO, format, ++i);
}

void			print_memory(void *addr, size_t size)
{
	size_t			i;
	size_t			j;
	unsigned char	*ptr;

	i = 0;
	ptr = addr;
	while ((size_t)ptr < (size_t)addr + size)
	{
		putnbr_hex(STDOUT_FILENO, *ptr, 2);
		(i % 2) ? write(STDOUT_FILENO, " ", 1) : 0;
		(i == 15) ? putstr_format(ptr - i, i) : 0;
		i = (i == 15) ? 0 : i + 1;
		++ptr;
	}
	if (i)
	{
		j = --i;
		while (++j < 16)
			write(STDOUT_FILENO, "   ", (j % 2) ? 3 : 2);
		putstr_format(ptr - i, i);
	}
}

void			malloc_print(void)
{
	size_t		i;
	t_malloc	*addr;

	i = 0;
	while (i < 3)
	{
		addr = g_malloc[i];
		while (addr)
		{
			print_memory(addr, addr->size);
			addr = addr->next;
		}
		++i;
	}
}
