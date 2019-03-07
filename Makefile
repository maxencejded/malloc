# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mjacques <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/03/06 17:36:23 by mjacques          #+#    #+#              #
#    Updated: 2019/03/06 17:36:27 by mjacques         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

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

FUNCTIONS		=
FILES			= $(addprefix srcs/, $(FUNCTIONS))
OBJECTS			= $(FILES:.c=.o)

.PHONY: all clean fclean re

all: $(NAME)

%.o: %.c
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(LIBFT):
	@make -C libft

$(NAME): $(LIBFT) $(OBJECTS)
	@$(CC) $(CFLAGS) -o $@ $(INCLUDES) $(OBJECTS) $(LIBFT)
	@ln -sf $@ libft_malloc.so

clean:
	@$(RM) $(OBJECTS)
	@make clean -C libft

fclean: clean
	@$(RM) $(NAME)
	@make fclean -C libft

re: fclean all
