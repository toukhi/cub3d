# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: abiru <abiru@student.42abudhabi.ae>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/09/24 16:03:13 by abiru             #+#    #+#              #
#    Updated: 2023/07/13 16:06:03 by abiru            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3D

HDRS = cub3D.h

SRCS = main.c ft_ssplit.c parser.c parsing_utils.c parsing_utils2.c \
		texture_parser.c color_parser.c map_parser.c window.c hooks.c \
		draw_minimap.c parse_minimap.c rays.c parsing_utils3.c

CC = cc -g3

CFLAGS = -Wextra -Werror -Wall

OBJS = $(SRCS:.c=.o)

LIBFT = ./libft/libft.a

LIBFT_DIR = ./libft

MLX_DIR = ./mlx

MLX		= ./mlx/libmlx.a

# for linux
# MLX_DIR = ./mlx_linux
# MLX		= ./mlx_linux/libmlx_Linux.a
# %.o: %.c
# $(CC) $(CFLAGS) -I/usr/include -Imlx_linux -O3 -c $< -o $@

all: $(NAME)

$(NAME): $(OBJS) $(HDRS)
	@make -C $(LIBFT_DIR)
	@make -C ${MLX_DIR}
	$(CC) $(CFLAGS) $(OBJS) -Lmlx -lmlx -framework OpenGL -framework AppKit $(LIBFT) -o $@
# for linux
# $(CC) $(CFLAGS) $(OBJS) -Lmlx_linux -lmlx_Linux -L/usr/lib -Imlx_linux -lXext -lX11 -lm -lz $(LIBFT) -o $@

%.o: %.c
	$(CC) $(CFLAGS) -Imlx -c $< -o $@

clean:
	@make clean -C $(LIBFT_DIR)
	rm -rf $(OBJS)
	@make clean -C ${MLX_DIR}

fclean: clean
	@make fclean -C $(LIBFT_DIR)
	rm -rf $(NAME)

bonus: all

re: fclean all

.PHONY: all clean fclean re bonus