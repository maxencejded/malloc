#include "malloc.h"

t_malloc		*g_malloc[3];

static t_malloc		*zone_new(size_t size, t_malloc *addr)
{
	t_malloc	*i;

	i = (t_malloc *)mmap(addr, size, PROT_READ | PROT_WRITE,
			MAP_ANON | MAP_PRIVATE, -1, 0);
	ft_bzero(i, size);
	i->use = sizeof(t_malloc);
	i->size = size;
	i->next = NULL;
	return (i);
}

/*
 * Create a new zone with the system call mmap.
 * If one zone is allocated, depending if the page is contigous
 * (if the address of the new = addr + size) they are merged to
 * make one big memory otherwise, it's add at in the pointer '*next'.
 */
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
		diff = (size_t)i - (size_t)(*addr) - (*addr)->size;
		if (diff == 0)
			(*addr)->size += size;
		else
			(*addr)->next = i;

	}
}

/*
 * Freedom the memory given by the system call mmap.
 * Do nothing it the addr point to NULL
 */
void		zone_free(t_malloc *addr)
{
	if (addr)
	{
		if (addr->next)
			zone_free(addr->next);
		munmap(addr, addr->size);
	}
}

static void	zone_print(t_malloc	*addr)
{
	if (addr)
	{
		print_memory(addr, addr->size);
		zone_print(addr->next);
	}
}

void		malloc_print()
{
	if (g_malloc[0])
		zone_print(g_malloc[0]);
	if (g_malloc[1])
		zone_print(g_malloc[1]);
	if (g_malloc[2])
		zone_print(g_malloc[2]);
}

size_t		zone_size(int i)
{
	if (i == 0)
		return (TINY_SIZE);
	else if (i == 1)
		return (SMALL_SIZE);
	return (LARGE_SIZE);
}
