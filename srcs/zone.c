#include "malloc.h"

/*
 * Create a new zone with the system call mmap.
 * If one zone is allocated, depending if the page is contigous
 * (if the address of the new = addr + size) they are merged to
 * make one big memory otherwise, it's add at in the pointer '*next'.
 */
void		zone_init(t_malloc **addr, size_t size)
{
	size_t	diff;

	diff = 0;
	if (*addr == NULL)
	{
		(*addr) = (t_malloc *)mmap(0, size, PROT_READ | PROT_WRITE,
				MAP_ANON | MAP_PRIVATE, -1, 0);
		// Change to ft_bzero
		bzero((*addr), size);
		(*addr)->use = sizeof(t_malloc);
		(*addr)->size = size;
		(*addr)->next = NULL;
	}
	else
	{
		(*addr)->next = (t_malloc *)mmap((*addr), size, PROT_READ | PROT_WRITE,
				MAP_ANON | MAP_PRIVATE, -1, 0);
		// Change to ft_bzero
		bzero((*addr)->next, size);
		diff = (size_t)(*addr)->next - (size_t)(*addr) - (*addr)->size;
		if (diff == 0)
			(*addr)->size += size;
		else
			(*addr)->next->size = size;
		(*addr)->next = (diff == 0) ? NULL : (*addr)->next;
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
		{
			write(1, "\n\n", 2);
			zone_free(addr->next);
		}
		munmap(addr, addr->size);
	}
}

void		zone_print(t_malloc *addr)
{
	if (addr)
	{
		print_memory(addr, addr->size);
		zone_print(addr->next);
	}
}

size_t		zone_size(int i)
{
	if (i == 0)
		return (TINY_SIZE);
	else if (i == 1)
		return (SMALL_SIZE);
	return (LARGE_SIZE);
}

