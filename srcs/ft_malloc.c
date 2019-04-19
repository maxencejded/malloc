#include "malloc.h"

t_malloc		*g_malloc[4];

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
	if (needed + addr->use <= addr->size)
	{
		elem = (t_header *)((char *)addr + addr->use);
		elem->flag = 1;
		elem->data = size;
		addr->use += needed;
		return (elem);
	}
	zone_init(&addr, zone_size(alloc_zone(size)));
	if (addr->next)
		return (alloc_find_new(addr->next, size));
	return (alloc_find_new(addr, size));
}

static void		*alloc_new(int i, size_t size)
{
	void		*ptr;
	t_header	*elem;

	ptr = NULL;
	elem = NULL;
	if (g_malloc[i] == NULL)
		zone_init(&g_malloc[i], zone_size(i));
	ptr = block_search(size);
	if (ptr == NULL)
	{
		if (i == 3 && g_malloc[i]->size - sizeof(t_malloc) < size)
			zone_init(&g_malloc[i], ((size % LARGE_SIZE) + 1) * LARGE_SIZE);
		elem = alloc_find_new(g_malloc[i], size);
		if (elem == NULL)
			return (NULL);
		ptr = elem + 1;
	}
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

void			*realloc(void *ptr, size_t size)
{
	int			i;
	void		*o;
	t_header	*elem;

	o = NULL;
	if (size == 0 || zone_search(ptr) == 2)
		return (NULL);
	if (ptr == NULL)
		return (malloc(size));
	i = alloc_zone(size);
	o = alloc_new(i, size);
	elem = (t_header *)ptr - 1;
	ft_memcpy(o, ptr, elem->data);
	free(ptr);
	return (o);
}
