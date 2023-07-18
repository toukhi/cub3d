# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yel-touk <yel-touk@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/09/24 16:03:13 by abiru             #+#    #+#              #
#    Updated: 2023/07/18 19:17:04 by yel-touk         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3D

NAME_BONUS = cub3D_bonus

HDRS = ./srcs/cub3D.h

HDRS_BONUS = ./bonus/cub3d_bonus.h

SRCS = ./srcs/main.c ./srcs/ft_ssplit.c ./srcs/parser.c ./srcs/parsing_utils.c ./srcs/parsing_utils2.c \
		./srcs/texture_parser.c ./srcs/color_parser.c ./srcs/map_parser.c ./srcs/window.c ./srcs/hooks.c \
		./srcs/draw_minimap.c ./srcs/parse_minimap.c ./srcs/rays.c ./srcs/parsing_utils3.c ./srcs/player.c \
		./srcs/sprite.c ./srcs/init.c ./srcs/draw_screen.c ./srcs/player_utils.c ./srcs/hooks2.c

SRCS_BONUS = ./bonus/main_bonus.c ./bonus/ft_ssplit_bonus.c ./bonus/parser_bonus.c \
			./bonus/parsing_utils_bonus.c ./bonus/parsing_utils2_bonus.c \
			./bonus/texture_parser_bonus.c ./bonus/color_parser_bonus.c \
			./bonus/map_parser_bonus.c ./bonus/window_bonus.c ./bonus/hooks_bonus.c \
			./bonus/draw_minimap_bonus.c ./bonus/parse_minimap_bonus.c ./bonus/rays_bonus.c \
			./bonus/parsing_utils3_bonus.c ./bonus/player_bonus.c ./bonus/sprite_bonus.c \
			./bonus/init_bonus.c ./bonus/draw_screen_bonus.c ./bonus/player_utils_bonus.c \
			./bonus/hooks2_bonus.c

CC = cc

CFLAGS = -Wextra -Werror -Wall

OBJS = $(SRCS:.c=.o)

OBJS_BONUS = $(SRCS_BONUS:.c=.o)

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
	rm -rf $(OBJS_BONUS)
	@make clean -C ${MLX_DIR}

fclean: clean
	@make fclean -C $(LIBFT_DIR)
	rm -rf $(NAME) $(NAME_BONUS)

bonus: $(OBJS_BONUS) $(HDRS_BONUS)
	@make -C $(LIBFT_DIR)
	@make -C ${MLX_DIR}
	$(CC) $(CFLAGS) $(OBJS_BONUS) -Lmlx -lmlx -framework OpenGL -framework AppKit $(LIBFT) -o $(NAME_BONUS)

re: fclean all

.PHONY: all clean fclean re bonus