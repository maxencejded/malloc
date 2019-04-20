#include "malloc.h"

t_malloc		*g_malloc[4];

static t_malloc		*zone_new(size_t size, t_malloc *addr)
{
	t_malloc	*i;

	i = (t_malloc *)mmap(addr, size, PROT_READ | PROT_WRITE,
			MAP_ANON | MAP_PRIVATE, -1, 0);
	if (i == MAP_FAILED)
		return (NULL);
	ft_bzero(i, size);
	i->use = S_MALLOC;
	i->size = size;
	i->next = NULL;
	return (i);
}

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
		if (i == NULL)
			return ;
		diff = (size_t)i - (size_t)(*addr) - (*addr)->size;
		if (diff == 0)
			(*addr)->size += size;
		else
			(*addr)->next = i;
	}
}

size_t				zone_size(int i, size_t size)
{
	if (i == 0)
		return (TINY_SIZE);
	else if (i == 1)
		return (SMALL_SIZE);
	return (((size % PAGE_SIZE) + 1) * PAGE_SIZE);
}

static int			page_search(t_malloc *addr, void *ptr)
{
	t_header	*elem;

	if ((size_t)addr < (size_t)ptr && (size_t)ptr < ((size_t)addr + addr->size))
	{
		elem = (t_header *)((char *)ptr - S_HEADER);
		if (elem && elem->flag == 1)
		{
			block_add(elem, ptr);
			return (1);
		}
		return (2);
	}
	return (0);
}

int					zone_search(void *ptr)
{
	int			i;
	int			ret;
	t_malloc	*tmp;

	i = 0;
	tmp = NULL;
	while (i < 3)
	{
		tmp = g_malloc[i];
		while (tmp)
		{
			ret = page_search(tmp, ptr);
			if (ret == 1)
				return (0);
			else if (ret == 2)
				return (2);
			tmp = tmp->next;
		}
		i += 1;
	}
	return (1);
}
