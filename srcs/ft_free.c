#include "malloc.h"

static int		desalloc_zone(size_t ptr)
{
	int			i;
	size_t		addr;

	i = 0;
	while (i < 3)
	{
		if (g_malloc[i] != NULL)
		{
			addr = (size_t)g_malloc[i];
			if (addr < ptr && ptr < (addr + g_malloc[i]->size))
				return (i);
		}
		i += 1;
	}
	return (-1);
}

static void		desalloc_double_free(void *ptr)
{
	write(2, "malloc: *** ", 13);
	write(2, "double free or corruption ", 27);
	write(2, "***\n", 4);
}

static void		desalloc_not_allocated(void *ptr)
{
	write(2, "malloc: *** ", 13);
	write(2, "pointer being freed was not allocated ", 39);
	write(2, "***\n", 4);
}

void			ft_free(void *ptr)
{
	int			i;
	t_header	*elem;

	elem = NULL;
	if (ptr == NULL)
		return ;
	i = desalloc_zone((size_t)ptr);
	if (i != -1)
	{
		elem = (t_header *)ptr - 1;
		if (elem && elem->flag == 1)
		{
			elem->flag = 0;
			// Remove bzero ?
			bzero(ptr, elem->data);
		}
		else
			desalloc_double_free(ptr);
	}
	else
		desalloc_not_allocated(ptr);
}
