#include "malloc.h"

void		block_add(t_header *i, void *ptr)
{
	t_free		*elem;
	t_malloc	*zone;

	if (g_malloc[3] == NULL)
		zone_init(&g_malloc[3], PAGE_SIZE);
	zone = g_malloc[3];
	if (zone == NULL)
		return ;
	elem = (t_free *)((char *)zone + S_MALLOC);
	while ((size_t)elem < (size_t)zone + zone->size)
	{
		if (elem->address == NULL)
			break ;
		elem = elem + 1;
		if ((size_t)elem >= (size_t)zone + zone->size)
		{
			if (zone->next == NULL)
				zone_init(&zone, PAGE_SIZE);
			zone = zone->next;
			elem = (t_free *)((char *)zone + S_MALLOC);
		}
	}
	elem->data = i->data;
	elem->address = ptr;
	zone->use += sizeof(t_free);
}

void		*block_search(size_t size)
{
	void		*ptr;
	t_free		*block;
	t_malloc	*zone;

	zone = g_malloc[3];
	if (g_malloc[3] == NULL)
		return (NULL);
	block = (t_free *)((char *)zone + S_MALLOC);
	while ((size_t)block < (size_t)zone + zone->use)
	{
		if (block && block->data >= size)
		{
			ptr = block->address;
			ft_bzero(block, sizeof(t_free));
			return (ptr);
		}
		block = block + 1;
	}
	return (NULL);
}
