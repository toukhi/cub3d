# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: abiru <abiru@student.42abudhabi.ae>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/09/24 16:03:13 by abiru             #+#    #+#              #
#    Updated: 2023/06/04 15:40:42 by abiru            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3D

SRCS = main.c ft_ssplit.c parser.c parsing_utils.c texture_parser.c color_parser.c map_parser.c

CC = cc -g3

CFLAGS = -Wextra -Werror -Wall

OBJS = $(SRCS:.c=.o)

LIBFT = ./libft/libft.a

LIBFT_DIR = ./libft

all: $(NAME)

$(NAME): $(OBJS)
	@make -C $(LIBFT_DIR)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) -o $@

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	@make clean -C $(LIBFT_DIR)
	rm -rf $(OBJS)

fclean: clean
	@make fclean -C $(LIBFT_DIR)
	rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re
