/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjacques <mjacques@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/20 17:25:26 by mjacques          #+#    #+#             */
/*   Updated: 2019/04/20 17:25:27 by mjacques         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

t_malloc		*g_malloc[3];

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
