/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   zone.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjacques <mjacques@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/20 17:25:21 by mjacques          #+#    #+#             */
/*   Updated: 2019/04/20 17:25:21 by mjacques         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

static t_malloc		*zone_new(size_t size, t_malloc *addr)
{
	t_malloc	*i;

	i = (t_malloc *)mmap(addr, size, PROT_READ | PROT_WRITE,
			MAP_ANON | MAP_PRIVATE, -1, 0);
	if (i == MAP_FAILED)
		return (NULL);
	ft_bzero(i, size);
	i->use = S_MALLOC;
	i->size = size;
	i->free = NULL;
	i->next = NULL;
	return (i);
}

void				zone_init(t_malloc **addr, size_t size)
{
	size_t		diff;
	t_malloc	*i;

	diff = 0;
	if (*addr == NULL)
		(*addr) = zone_new(size, 0);
	else
	{
		i = zone_new(size, *addr);
		if (i == NULL)
			return ;
		diff = (size_t)i - (size_t)(*addr) - (*addr)->size;
		if (diff == 0)
			(*addr)->size += size;
		else
			(*addr)->next = i;
	}
}

size_t				zone_size(int i, size_t size)
{
	if (i == 0)
		return (TINY_SIZE);
	else if (i == 1)
		return (SMALL_SIZE);
	return (((size % PAGE_SIZE) + 1) * PAGE_SIZE);
}

static int			page_search(int i, t_malloc *addr, void *ptr, int keep)
{
	t_header	*elem;

	if ((size_t)addr < (size_t)ptr && (size_t)ptr < ((size_t)addr + addr->size))
	{
		elem = (t_header *)((char *)ptr - S_HEADER);
		if (elem && elem->flag == 1)
		{
			if (keep == 0)
			{
				elem->flag = 0;
				block_add(i, ptr);
			}
			return (1);
		}
		return (2);
	}
	return (0);
}

int					zone_search(void *ptr, int keep)
{
	int			i;
	int			ret;
	t_malloc	*addr;

	i = 0;
	addr = NULL;
	while (i < 3)
	{
		addr = g_malloc[i];
		while (addr)
		{
			ret = page_search(i, addr, ptr, keep);
			if (ret == 1)
				return (0);
			else if (ret == 2)
				return (2);
			addr = addr->next;
		}
		i += 1;
	}
	return (1);
}
