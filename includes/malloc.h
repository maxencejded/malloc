/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjacques <mjacques@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/20 17:25:39 by mjacques          #+#    #+#             */
/*   Updated: 2019/05/25 16:33:44 by mjacques         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
# define TINY_SIZE	PAGE_SIZE * 32
# define SMALL_SIZE	PAGE_SIZE * 256

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
	struct s_free		*next;
}						t_free;

typedef struct			s_malloc
{
	size_t				use;
	size_t				size;
	void				*free;
	struct s_malloc		*next;
}						t_malloc;

extern t_malloc			*g_malloc[3];

void					putnbr_hex(int fd, size_t nbr, int size);
void					print_memory(void *addr, size_t size);
void					malloc_print(void);

void					show_alloc_mem(void);
void					print_ptr(size_t ptr, int fd);

void					zone_init(t_malloc **addr, size_t size);
size_t					zone_size(int i, size_t size);
int						zone_search(void *ptr, int keep);

void					block_add(int i, void *addr);
void					*block_search(int i, size_t size);

void					*malloc(size_t size);
void					*realloc(void *ptr, size_t size);

void					free(void *ptr);

void					ft_bzero(void *s, size_t n);
void					*ft_memcpy(void *dst, const void *src, size_t n);

#endif
