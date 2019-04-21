/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   block.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjacques <mjacques@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/20 17:25:18 by mjacques          #+#    #+#             */
/*   Updated: 2019/04/20 17:25:18 by mjacques         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

static void		defragment_free(t_free *elem, t_free *current)
{
	t_header	*lower;
	t_header	*higher;

	lower = (t_header *)((char *)elem - sizeof(t_header));
	higher = (t_header *)((char *)current - sizeof(t_header));
	if ((size_t)lower + lower->data + sizeof(t_header) == (size_t)higher)
	{
		lower->data += higher->data + sizeof(t_header);
		elem->next = current->next;
	}
}

static void		block_insert(t_malloc *addr, t_free *elem)
{
	t_free		*current;
	t_free		*previous;

	current = addr->free;
	previous = NULL;
	while (current != NULL)
	{
		if (current > elem)
		{
			elem->next = current;
			if (previous == NULL)
			{
				addr->free = elem;
				defragment_free(elem, current);
				return ;
			}
			break ;
		}
		previous = current;
		current = current->next;
	}
	previous->next = elem;
	defragment_free(previous, elem);
}

void			block_add(int i, void *addr)
{
	t_free		*elem;

	if (g_malloc[i] == NULL)
		return ;
	elem = (t_free *)addr;
	elem->next = NULL;
	if (g_malloc[i]->free == NULL)
		g_malloc[i]->free = elem;
	else
		block_insert(g_malloc[i], elem);
}

void			*block_search(int i, size_t size)
{
	t_free		*current;
	t_free		*previous;
	t_header	*elem;

	if (g_malloc[i] == NULL || g_malloc[i]->free == NULL)
		return (NULL);
	current = g_malloc[i]->free;
	previous = NULL;
	while (current != NULL)
	{
		elem = (t_header *)((char *)current - sizeof(t_header));
		if (elem && size <= elem->data)
		{
			elem->flag = 1;
			if (previous == NULL)
				g_malloc[i]->free = current->next;
			else
				previous->next = current->next;
			return ((void *)current);
		}
		previous = current;
		current = current->next;
	}
	return (NULL);
}
