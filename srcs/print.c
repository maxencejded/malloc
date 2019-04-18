#include "malloc.h"

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

void		error_double_free(size_t ptr)
{
	write(2, "malloc: *** ", 12);
	write(2, "double free or corruption : ", 29);
	print_ptr((size_t)ptr, 2);
	write(2, " ***\n", 5);
}

void		error_not_allocated(size_t ptr)
{
	write(2, "malloc: *** ", 12);
	write(2, "pointer being freed was not allocated : ", 40);
	print_ptr((size_t)ptr, 2);
	write(2, " ***\n", 5);
}

