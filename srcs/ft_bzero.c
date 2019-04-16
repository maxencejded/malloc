#include "malloc.h"

void	ft_bzero(void *s, size_t n)
{
	size_t	i;
	char	*str;

	str = (char *)s;
	if (n != 0)
	{
		i = 0;
		while (i < n)
		{
			str[i] = 0;
			i++;
		}
	}
}
