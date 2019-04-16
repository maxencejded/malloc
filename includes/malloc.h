#ifndef MALLOC_H
# define MALLOC_H

# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <sys/mman.h>
# include <sys/resource.h>

# pragma pack(1)

# define PAGE_SIZE	getpagesize()
# define TINY_SIZE	PAGE_SIZE * 10
# define SMALL_SIZE	PAGE_SIZE * 20
# define LARGE_SIZE	PAGE_SIZE * 30

# define TINY_MAX	PAGE_SIZE / 4
# define SMALL_MAX	PAGE_SIZE * 2

typedef struct			s_header
{
	char				flag;
	size_t				data;
}						t_header;

typedef struct			s_malloc
{
	size_t				use;
	size_t				size;
	struct s_malloc		*next;
}						t_malloc;

extern t_malloc			*g_malloc[3];

// void		*realloc(void *ptr, size_t size);
// void		show_alloc_mem();
void			print_memory(void *addr, size_t size);

void			zone_init(t_malloc **addr, size_t size);
void			zone_free(t_malloc *addr);
void			zone_print(t_malloc *addr);
size_t			zone_size(int i);

// void					*malloc(size_t size);
void			*ft_malloc(size_t size);

// void		free(void *ptr);
void			ft_free(void *ptr);

#endif
