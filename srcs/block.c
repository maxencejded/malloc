#include "malloc.h"

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
				addr->free = NULL;
			else
				previous->next = elem;
			return ;
		}
		previous = current;
		current = current->next;
	}
	previous->next = elem;
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
