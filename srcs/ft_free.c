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
	write(STDERR_FILENO, "malloc: *** ", 12);
	write(STDERR_FILENO, "double free or corruption : ", 29);
	print_ptr(STDERR_FILENO, (size_t)ptr);
	write(STDERR_FILENO, " ***\n", 5);
}

static void		error_not_allocated(size_t ptr)
{
	write(STDERR_FILENO, "malloc: *** ", 12);
	write(STDERR_FILENO, "pointer being freed was not allocated : ", 40);
	print_ptr(STDERR_FILENO, (size_t)ptr);
	write(STDERR_FILENO, " ***\n", 5);
}

void			free(void *ptr)
{
	int		ret;

	ret = 0;
	if (ptr == NULL)
		return ;
	ret = zone_search(ptr, 0);
	if (ret == FREE_FAILURE)
		error_not_allocated((size_t)ptr);
	if (ret == FREE_DOUBLE)
		error_double_free((size_t)ptr);
}
