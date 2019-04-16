#include "malloc.h"

t_malloc		*g_malloc[3];

static int		alloc_zone(size_t size)
{
	int		i;

	i = 2;
	if (size < TINY_MAX)
		i = 0;
	else if (size < SMALL_MAX)
		i = 1;
	return (i);
}

static t_header	*alloc_find_new(t_malloc *addr, size_t size)
{
	size_t		needed;
	t_header	*elem;

	elem = NULL;
	needed = size + sizeof(t_header);
	if (needed <= addr->size - addr->use)
	{
		elem = (t_header *)((char *)addr + addr->use);
		elem->flag = 1;
		elem->data = size;
		addr->use += needed;
		return (elem);
	}
	zone_init(&addr, PAGE_SIZE);
	if (addr->next)
		return (alloc_find_new(addr->next, size));
	return (alloc_find_new(addr, size));
}

static t_header	*alloc_find_free(t_malloc *addr, size_t size)
{
	size_t		position;
	t_header	*elem;

	elem = NULL;
	if (addr == NULL)
		return (NULL);
	position = sizeof(t_malloc);
	elem = (t_header *)((char *)addr + sizeof(t_malloc));
	while (elem && position < addr->use)
	{
		if (elem->flag == 0)
		{
			if (elem->data >= size)
				return (elem);
		}
		elem = (t_header *)((char *)elem + elem->data + sizeof(t_header));
		position += elem->data + sizeof(t_header);
	}
	return (NULL);

}

static void		*alloc_new(int i, size_t size)
{
	void		*ptr;
	t_header	*elem;

	ptr = NULL;
	elem = NULL;
	if (g_malloc[i] == NULL)
		zone_init(&g_malloc[i], zone_size(i));
	elem = alloc_find_free(g_malloc[i], size);
	if (elem == NULL)
	{
		if (i == 3 && g_malloc[i]->size - sizeof(t_malloc) < size)
			zone_init(&g_malloc[i], ((size % LARGE_SIZE) + 1) * LARGE_SIZE);
		elem = alloc_find_new(g_malloc[i], size);
	}
	if (elem == NULL)
		return (NULL);
	ptr = elem + 1;
	return (ptr);
}

void			*malloc(size_t size)
{
	int		i;
	void	*ptr;

	ptr = NULL;
	if (size == 0)
		return (NULL);
	i = alloc_zone(size);
	ptr = alloc_new(i, size);
	return (ptr);
}
