#ifndef MALLOC_H
# define MALLOC_H

# include <stdlib.h>
# include <unistd.h>
# include <sys/mman.h>
# include <sys/resource.h>

/*
** Reduce the size of the struct with
** # pragma pack(1)
** The idea is to align the struct on 1 byte
** in place of 4 ususally
*/

# define PAGE_SIZE	getpagesize()
# define TINY_SIZE	PAGE_SIZE * 10
# define SMALL_SIZE	PAGE_SIZE * 20
# define LARGE_SIZE	PAGE_SIZE * 30

# define TINY_MAX	(size_t)PAGE_SIZE / 4
# define SMALL_MAX	(size_t)PAGE_SIZE * 2

# define S_MALLOC	sizeof(t_malloc)
# define S_HEADER	sizeof(t_header)

typedef struct			s_header
{
	char				flag;
	size_t				data;
}						t_header;

typedef struct			s_free
{
	size_t				data;
	void				*address;
}						t_free;

typedef struct			s_malloc
{
	size_t				use;
	size_t				size;
	struct s_malloc		*next;
}						t_malloc;

extern t_malloc			*g_malloc[4];

void					print_memory(void *addr, size_t size);
void					print_ptr(size_t ptr, int fd);

void					show_alloc_mem(void);
void					malloc_print(void);
void					error_double_free(size_t ptr);
void					error_not_allocated(size_t ptr);

void					zone_init(t_malloc **addr, size_t size);
size_t					zone_size(int i);
int						zone_search(void *ptr);

void					block_add(t_header *i, void *ptr);
void					*block_search(size_t size);

void					*malloc(size_t size);
void					*realloc(void *ptr, size_t size);

void					free(void *ptr);

void					ft_bzero(void *s, size_t n);
void					*ft_memcpy(void *dst, const void *src, size_t n);

#endif
