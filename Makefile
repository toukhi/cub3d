# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yel-touk <yel-touk@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/09/24 16:03:13 by abiru             #+#    #+#              #
#    Updated: 2023/06/11 16:32:54 by yel-touk         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3D

SRCS = main.c ft_ssplit.c parser.c parsing_utils.c parsing_utils2.c texture_parser.c color_parser.c map_parser.c

CC = cc -g3

CFLAGS = -Wextra -Werror -Wall

OBJS = $(SRCS:.c=.o)

LIBFT = ./libft/libft.a

LIBFT_DIR = ./libft

MLX		= mlx/libmlx.a

all: $(NAME)

$(NAME): $(OBJS)
	@make -C $(LIBFT_DIR)
	$(CC) $(CFLAGS) $(OBJS) -Lmlx -lmlx -framework OpenGL -framework AppKit $(LIBFT) -o $@

%.o: %.c
	$(CC) $(CFLAGS) -Imlx -c $< -o $@

clean:
	@make clean -C $(LIBFT_DIR)
	rm -rf $(OBJS)
	@make clean -C mlx

fclean: clean
	@make fclean -C $(LIBFT_DIR)
	rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re
