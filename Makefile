# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: youssef <youssef@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/09/24 16:03:13 by abiru             #+#    #+#              #
#    Updated: 2023/06/16 15:24:17 by youssef          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3D

SRCS = main.c ft_ssplit.c parser.c parsing_utils.c parsing_utils2.c texture_parser.c color_parser.c map_parser.c window.c hooks.c draw_minimap.c

CC = cc -g3

CFLAGS = -Wextra -Werror -Wall

OBJS = $(SRCS:.c=.o)

LIBFT = ./libft/libft.a

LIBFT_DIR = ./libft

MLX_DIR = ./mlx

MLX		= ./mlx/libmlx.a

all: $(NAME)

$(NAME): $(OBJS)
	@make -C $(LIBFT_DIR)
	@make -C ${MLX_DIR}
	$(CC) $(CFLAGS) $(OBJS) -Lmlx -lmlx -framework OpenGL -framework AppKit $(LIBFT) -o $@

%.o: %.c
	$(CC) $(CFLAGS) -Imlx -c $< -o $@

clean:
	@make clean -C $(LIBFT_DIR)
	rm -rf $(OBJS)
	@make clean -C ${MLX_DIR}

fclean: clean
	@make fclean -C $(LIBFT_DIR)
	rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re
