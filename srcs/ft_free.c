#include "malloc.h"

t_malloc		*g_malloc[4];

static void		free_block_add(t_header *i, void *ptr)
{
	size_t		size;
	t_free		*elem;
	t_malloc	*zone;

	size = sizeof(t_malloc);
	elem = NULL;
	zone = NULL;
	if (g_malloc[3] == NULL)
		zone_init(&g_malloc[3], PAGE_SIZE);
	zone = g_malloc[3];
	elem = (t_free *)((char *)zone + sizeof(t_malloc));
	while (size < zone->size)
	{
		if (elem->address == NULL)
			break ;
		elem = elem + 1;
		size += sizeof(t_free);
		if (size >= zone->size)
		{
			size = sizeof(t_malloc);
			if (zone->next == NULL)
				zone_init(&zone, PAGE_SIZE);
			zone = zone->next;
			elem = (t_free *)((char *)zone + sizeof(t_malloc));
		}
	}
	elem->data = i->data;
	elem->address = ptr;
	zone->use += sizeof(t_free);
}

static int		dealloc_search_page(t_malloc *addr, void *ptr)
{
	t_header	*elem;

	if ((size_t)addr < (size_t)ptr && (size_t)ptr < ((size_t)addr + addr->size))
	{
		elem = (t_header *)ptr - 1;
		if (elem)
			free_block_add(elem, ptr);
		else
			error_double_free((size_t)ptr);
		return (1);
	}
	return (0);
}

static int		dealloc_search_zone(void *ptr)
{
	int			i;
	t_malloc	*tmp;

	i = 0;
	tmp = NULL;
	while (i < 3)
	{
		tmp = g_malloc[i];
		while (tmp)
		{
			if (dealloc_search_page(tmp, ptr) == 1)
				return (1);
			tmp = tmp->next;
		}
		i += 1;
	}
	error_not_allocated((size_t)ptr);
	return (0);
}

void			free(void *ptr)
{
	if (ptr == NULL)
		return ;
	dealloc_search_zone(ptr);
}
