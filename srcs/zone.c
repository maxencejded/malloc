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
	t_malloc	*zone;

	zone = (t_malloc *)mmap(addr, size, PROT_READ | PROT_WRITE,
			MAP_ANON | MAP_PRIVATE, -1, 0);
	if (zone == MAP_FAILED)
		return (NULL);
	ft_bzero(zone, size);
	zone->use = S_MALLOC;
	zone->size = size;
	zone->free = NULL;
	zone->next = NULL;
	return (zone);
}

void				zone_init(t_malloc **addr, size_t size)
{
	size_t		diff;
	t_malloc	*zone;
	t_malloc	*tmp;

	diff = 0;
	if (*addr == NULL)
		(*addr) = zone_new(size, 0);
	else
	{
		zone = zone_new(size, *addr);
		if (zone == NULL)
			return ;
		diff = (size_t)zone - (size_t)(*addr) - (*addr)->size;
		if (diff == 0)
			(*addr)->size += size;
		else
		{
			tmp = *addr;
			while (tmp->next)
				tmp = tmp->next;
			tmp->next = zone;
		}
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
		elem = (t_header *)ptr - 1;
		if (elem && elem->flag == 1)
		{
			if (keep == 0)
			{
				elem->flag = 0;
				block_add(i, ptr);
			}
			return (FREE_SUCCESS);
		}
		return (FREE_DOUBLE);
	}
	return (FREE_FAILURE);
}

int					zone_search(void *ptr, int keep)
{
	int			i;
	short		ret;
	t_malloc	*addr;

	i = 0;
	addr = NULL;
	while (i < 3)
	{
		addr = g_malloc[i];
		while (addr)
		{
			ret = page_search(i, addr, ptr, keep);
			if (ret == FREE_SUCCESS)
				return (FREE_SUCCESS);
			else if (ret == FREE_DOUBLE)
				return (FREE_DOUBLE);
			addr = addr->next;
		}
		++i;
	}
	return (FREE_FAILURE);
}
