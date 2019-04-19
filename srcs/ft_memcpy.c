#include "malloc.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t			i;
	unsigned char	*newdst;
	unsigned char	*newsrc;

	newdst = (unsigned char *)dst;
	newsrc = (unsigned char *)src;
	i = 0;
	while (i < n)
	{
		newdst[i] = newsrc[i];
		i++;
	}
	return (dst);
}
