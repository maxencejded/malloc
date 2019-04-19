#include "malloc.h"

static void		ft_putchar(char c)
{
	write(1, &c, 1);
}

static void		ft_putnbr(size_t n)
{
	if (n >= 10)
	{
		ft_putnbr(n / 10);
		ft_putchar((n % 10) + 48);
	}
	if (n < 10)
		ft_putchar(n + 48);
}

static void		show_alloc_zone(t_malloc *addr, size_t *total)
{
	t_header	*elem;

	elem = (t_header *)((char *)addr + sizeof(t_malloc));
	while ((size_t)elem < (size_t)addr + addr->use)
	{
		if (elem && elem->flag == 1)
		{
			print_ptr((size_t)elem, 1);
			write(1, " - ", 3);
			print_ptr((size_t)elem + elem->data, 1);
			write(1, " : ", 3);
			ft_putnbr(elem->data);
			write(1, " bytes\n", 7);
			*total += elem->data;
		}
		elem = (t_header *)((char *)elem + elem->data + sizeof(t_header));
	}
	if (addr->next)
	{
		write(1, "NEXT  : ", 8);
		print_ptr((size_t)addr->next, 1);
		write(1, "\n", 1);
		show_alloc_zone(addr->next, total);
	}
}

void			show_alloc_mem(void)
{
	int			i;
	size_t		total;

	i = 0;
	total = 0;
	while (i < 3)
	{
		(i == 0) ? write(1, "TINY : ", 7) : 0;
		(i == 1) ? write(1, "SMALL : ", 8) : 0;
		(i == 2) ? write(1, "LARGE : ", 8) : 0;
		print_ptr((size_t)g_malloc[i], 1);
		write(1, "\n", 1);
		if (g_malloc[i] != NULL)
			show_alloc_zone(g_malloc[i], &total);
		i += 1;
	}
	write(1, "Total : ", 8);
	ft_putnbr(total);
	write(1, " bytes\n", 7);
}
