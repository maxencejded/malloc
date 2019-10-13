/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_malloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjacques <mjacques@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/20 17:25:35 by mjacques          #+#    #+#             */
/*   Updated: 2019/04/20 17:25:35 by mjacques         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

t_malloc		*g_malloc[3];

static int		alloc_zone(size_t size)
{
	if (size <= TINY_MAX)
		return (0);
	else if (size <= SMALL_MAX)
		return (1);
	return (2);
}

static void		*alloc_find_new(t_malloc *addr, size_t size)
{
	t_header	*elem;

	if (addr == NULL)
		return (NULL);
	if (size + S_HEADER + addr->use <= addr->size)
	{
		elem = (t_header *)((char *)addr + addr->use);
		elem->flag = 1;
		elem->data = size;
		addr->use += size + S_HEADER;
		return (elem + 1);
	}
	zone_init(&addr, zone_size(alloc_zone(size), size));
	if (addr->next)
		return (alloc_find_new(addr->next, size));
	return (alloc_find_new(addr, size));
}

static void		*alloc_new(int i, size_t size)
{
	void		*ptr;

	ptr = NULL;
	if (g_malloc[i] == NULL)
		zone_init(&g_malloc[i], zone_size(i, size));
	ptr = block_search(i, size);
	if (ptr == NULL && g_malloc[i] != NULL)
		ptr = alloc_find_new(g_malloc[i], size);
	return (ptr);
}

void			*malloc(size_t size)
{
	int		i;
	void	*ptr;

	ptr = NULL;
	if (size == 0)
		return (NULL);
	size = (size < sizeof(t_free)) ? sizeof(t_free) : size;
	i = alloc_zone(size);
	ptr = alloc_new(i, size);
	return (ptr);
}

void			*realloc(void *ptr, size_t size)
{
	int			i;
	void		*nptr;
	t_header	*elem;

	if (ptr == NULL)
		return (malloc(size));
	if (zone_search(ptr, 1) != FREE_SUCCESS)
		return (NULL);
	i = alloc_zone(size);
	elem = (t_header *)ptr - 1;
	if (g_malloc[i]
		&& elem->data + S_HEADER + S_MALLOC == g_malloc[i]->use
		&& size + S_HEADER <= g_malloc[i]->size - S_MALLOC)
	{
		elem->data = size;
		return (ptr);
	}
	nptr = alloc_new(i, size);
	ft_memcpy(nptr, ptr, (elem->data > size) ? size : elem->data);
	zone_search(ptr, 0);
	return (nptr);
}
