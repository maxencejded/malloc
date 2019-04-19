#include "malloc.h"

t_malloc		*g_malloc[4];

static int		dealloc_search_page(t_malloc *addr, void *ptr)
{
	t_header	*elem;

	if ((size_t)addr < (size_t)ptr && (size_t)ptr < ((size_t)addr + addr->size))
	{
		elem = (t_header *)ptr - 1;
		if (elem && elem->flag == 1)
			block_add(elem, ptr);
		else
			error_double_free((size_t)ptr);
		elem->flag = 0;
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
