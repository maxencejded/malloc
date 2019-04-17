#include "malloc.h"

t_malloc		*g_malloc[3];

static void		dealloc_double_free(size_t ptr)
{
	write(2, "malloc: *** ", 12);
	write(2, "double free or corruption : ", 29);
	print_ptr((size_t)ptr, 2);
	write(2, " ***\n", 5);
}

static void		dealloc_not_allocated(size_t ptr)
{
	write(2, "malloc: *** ", 12);
	write(2, "pointer being freed was not allocated : ", 40);
	print_ptr((size_t)ptr, 2);
	write(2, " ***\n", 5);
}

static int		dealloc_page(t_malloc *addr, size_t ptr)
{
	t_header	*elem;

	if ((size_t)addr < ptr && ptr < ((size_t)addr + addr->size))
	{
		elem = (t_header *)ptr - 1;
		if (elem && elem->flag == 1)
		{
			elem->flag = 0;
			ft_bzero((void *)ptr, elem->data);
		}
		else
			dealloc_double_free(ptr);
		return (1);
	}
	return (0);
}

static int		dealloc_zone(size_t ptr)
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
			if (dealloc_page(tmp, ptr) == 1)
				return (1);
			tmp = tmp->next;
		}
		i += 1;
	}
	dealloc_not_allocated(ptr);
	return (0);
}

void			free(void *ptr)
{
	if (ptr == NULL)
		return ;
	dealloc_zone((size_t)ptr);
}
