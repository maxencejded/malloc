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
