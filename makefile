# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aoussama <aoussama@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/04/21 14:41:13 by nafarid           #+#    #+#              #
#    Updated: 2025/07/25 13:38:15 by aoussama         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
SRC = main.c utils.c pars.c cheking_lexer.c test_function.c check_dolar.c utils1.c expand2.c
OBJS = $(SRC:.c=.o)
CC = cc
CFLAGS = -Wall -Werror -Wextra -g3
FLAGS = -lreadline
LIBFT_DIR = libft
LIB = $(LIBFT_DIR)/libft.a
all: $(NAME)

$(NAME) : $(OBJS)
	@cd $(LIBFT_DIR) && $(MAKE) 
	@$(CC) $(CFLAGS) $(OBJS) $(LIB) -o $(NAME) $(FLAGS)

%.o :%.c
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	cd $(LIBFT_DIR) && $(MAKE) clean
	rm -f $(OBJS)

fclean: clean
	cd $(LIBFT_DIR) && $(MAKE) fclean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re