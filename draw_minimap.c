/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_minimap.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youssef <youssef@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/15 14:24:48 by yel-touk          #+#    #+#             */
/*   Updated: 2023/07/16 18:50:23 by youssef          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	get_color(char c)
{
	if (c == '1')
		return (GRAY);
	return (WHITE);
}

void	draw_square(t_data *data, t_vector pixel_pos, size_t size, int color)
{
	size_t	i;
	size_t	j;

	i = 0;
	while (i < size)
	{
		j = 0;
		while (j++ < size)
		{
			my_mlx_pixel_put(data, pixel_pos.x, pixel_pos.y, color);
			pixel_pos.x++;
		}
		pixel_pos.x -= j - 1;
		i++;
		pixel_pos.y++;
	}
}

void	player_to_pixel(t_vector pos, t_vector *pixel)
{
	pixel->x = pos.x * BLOCK_SIZE;
	pixel->y = pos.y * BLOCK_SIZE;
}

void	draw_minimap(t_vars *vars)
{
	int			i;
	int			j;
	t_vector	pixel_pos;
	int			a;
	int			b;
	int			tmp_a;
	int			tmp_b;
	int block_size;

	block_size = BLOCK_SIZE;
	if (vars->scene.size < MAP_HEIGHT / BLOCK_SIZE)
		block_size = MAP_HEIGHT / vars->scene.size;
	i = 0;
	pixel_pos.y = MAP_PADDING;
	a = vars->player.pos.y -  MAP_HEIGHT / block_size / 2;
	while (i < MAP_HEIGHT / block_size && i < (int)vars->scene.size)
	{
		pixel_pos.x = MAP_PADDING;
		j = 0;
		b = vars->player.pos.x -  MAP_WIDTH / block_size / 2;
		tmp_a = a;
		if (a < 0)
			tmp_a = 0;
		if (a >= (int) vars->scene.size)
			tmp_a = vars->scene.size -1;
		while (j < MAP_WIDTH / block_size)
		{
			tmp_b = b;
			if (b < 0)
				tmp_b = 0;
			if (tmp_b >= (int) ft_strlen(vars->scene.minimap[i]))
				tmp_b = (int) ft_strlen(vars->scene.minimap[i]) - 1;
			draw_square(&vars->image, pixel_pos, block_size, get_color(vars->scene.minimap[tmp_a][tmp_b]));
			pixel_pos.x += block_size;
			j++;
			b++;
		}
		i++;
		a++;
		pixel_pos.y += block_size;
	}
	pixel_pos.x = MAP_WIDTH / 2;
	pixel_pos.y = MAP_HEIGHT / 2;
	draw_square(&vars->image, pixel_pos, 4, RED);
}

// void	draw_minimap(t_vars *vars)
// {
// 	size_t		i;
// 	size_t		j;
//     t_vector	pixel_pos;
	
// 	i = 0;
//     pixel_pos.y = 0;
// 	while (i < vars->scene.size && i < WIN_HEIGHT - BLOCK_SIZE)
// 	{
//         pixel_pos.x = 0;
// 		j = 0;
// 		while (j < ft_strlen(vars->scene.minimap[i]) )//&& j < WIN_WIDTH - BLOCK_SIZE)
// 		{
//             draw_square(&vars->image, pixel_pos, BLOCK_SIZE, get_color(vars->scene.minimap[i][j]));
//             pixel_pos.x += BLOCK_SIZE;
//             j++;
// 		}
// 		i++;
//         pixel_pos.y += BLOCK_SIZE;
// 	}
// 	player_to_pixel(vars->player.pos, &pixel_pos);
// 	draw_square(&vars->image, pixel_pos, 3, RED);
// }
