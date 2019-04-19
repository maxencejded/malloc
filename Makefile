ifeq ($(HOSTTYPE),)
	HOSTTYPE	:= $(shell uname -m)_$(shell uname -s)
endif

CC				= gcc
RM				= rm -f
NAME			= libft_malloc_$(HOSTTYPE).so
CFLAGS			= -Wall -Wextra -Werror
INCLUDES		= -I includes

FUNCTIONS		= ft_malloc.c ft_free.c zone.c block.c
PRINT			= print.c show_alloc.c print_memory.c
LIBFT			= ft_bzero.c ft_memcpy.c
FILES			= $(addprefix srcs/, $(FUNCTIONS) $(PRINT) $(LIBFT))
OBJECTS			= $(FILES:.c=.o)

.PHONY: all clean fclean re

all: $(NAME)

%.o: %.c
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(NAME): $(OBJECTS)
	@$(CC) $(CFLAGS) -shared -o $@ $(INCLUDES) $(OBJECTS)
	@ln -sf $@ libft_malloc.so

clean:
	@$(RM) $(OBJECTS)

fclean: clean
	@$(RM) $(NAME)
	@$(RM) libft_malloc.so

re: fclean all
