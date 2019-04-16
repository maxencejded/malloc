ifeq ($(HOSTTYPE),)
	HOSTTYPE	:= $(shell uname -m)_$(shell uname -s)
endif

CC				= gcc
RM				= rm -f
NAME			= libft_malloc_$(HOSTTYPE).so
CFLAGS			= -Wall -Wextra -Werror -g
LIBFT 			= libft/libft.a
INCLUDES		= -I includes\
				  -I libft/includes

FUNCTIONS		= ft_malloc.c ft_free.c zone.c print_memory.c
FILES			= $(addprefix srcs/, $(FUNCTIONS))
OBJECTS			= $(FILES:.c=.o)

.PHONY: all clean fclean re

all: $(NAME)

%.o: %.c
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(LIBFT):
	@make -C libft

$(NAME): $(OBJECTS) #$(LIBFT)
	@$(CC) $(CFLAGS) -o $@ $(INCLUDES) $(OBJECTS) $(LIBFT)
	@ln -sf $@ libft_malloc.so

clean:
	@$(RM) $(OBJECTS)
	@make clean -C libft

fclean: clean
	@$(RM) $(NAME)
	@make fclean -C libft

re: fclean all
