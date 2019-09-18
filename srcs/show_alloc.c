/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show_alloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjacques <mjacques@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/20 17:25:24 by mjacques          #+#    #+#             */
/*   Updated: 2019/09/17 19:55:49 by mjacques         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

static void		show_alloc_zone(t_malloc *addr, size_t *total)
{
	t_header	*elem;

	elem = (t_header *)((char *)addr + S_MALLOC);
	while ((size_t)elem < (size_t)addr + addr->use)
	{
		if (elem && elem->flag == 1)
		{
			print_ptr(STDOUT_FILENO, (size_t)elem);
			write(STDOUT_FILENO, " - ", 3);
			print_ptr(STDOUT_FILENO, (size_t)elem + elem->data);
			write(STDOUT_FILENO, " : ", 3);
			print_ptr(STDOUT_FILENO, elem->data);
			write(STDOUT_FILENO, " bytes\n", 7);
			*total += elem->data;
		}
		elem = (t_header *)((char *)elem + elem->data + S_HEADER);
	}
	if (addr->next)
	{
		write(STDOUT_FILENO, "NEXT  : ", 8);
		print_ptr(STDOUT_FILENO, (size_t)addr->next);
		write(STDOUT_FILENO, "\n", 1);
		show_alloc_zone(addr->next, total);
	}
}

void			show_alloc_mem(void)
{
	size_t		i;
	size_t		total;

	i = 0;
	total = 0;
	while (i < 3)
	{
		(i == 0) ? write(1, "TINY  : ", 8) : 0;
		(i == 1) ? write(1, "SMALL : ", 8) : 0;
		(i == 2) ? write(1, "LARGE : ", 8) : 0;
		print_ptr(STDOUT_FILENO, (size_t)g_malloc[i]);
		write(STDOUT_FILENO, "\n", 1);
		if (g_malloc[i] != NULL)
			show_alloc_zone(g_malloc[i], &total);
		++i;
	}
	write(STDOUT_FILENO, "Total : ", 8);
	print_ptr(STDOUT_FILENO, total);
	write(STDOUT_FILENO, " bytes\n", 7);
}

void			print_ptr(int fd, size_t ptr)
{
	write(STDOUT_FILENO, "0x", 2);
	putnbr_hex(fd, ptr, 16);
}
