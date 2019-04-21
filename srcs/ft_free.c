/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjacques <mjacques@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/20 17:25:26 by mjacques          #+#    #+#             */
/*   Updated: 2019/04/20 17:34:30 by mjacques         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

t_malloc		*g_malloc[3];

static void		error_double_free(size_t ptr)
{
	write(2, "malloc: *** ", 12);
	write(2, "double free or corruption : ", 29);
	print_ptr((size_t)ptr, 2);
	write(2, " ***\n", 5);
}

static void		error_not_allocated(size_t ptr)
{
	write(2, "malloc: *** ", 12);
	write(2, "pointer being freed was not allocated : ", 40);
	print_ptr((size_t)ptr, 2);
	write(2, " ***\n", 5);
}

void			free(void *ptr)
{
	int		ret;

	ret = 0;
	if (ptr == NULL)
		return ;
	ret = zone_search(ptr, 0);
	if (ret == 1)
		error_not_allocated((size_t)ptr);
	if (ret == 2)
		error_double_free((size_t)ptr);
}
