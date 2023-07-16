/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_minimap.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youssef <youssef@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/15 14:24:48 by yel-touk          #+#    #+#             */
/*   Updated: 2023/07/17 00:13:17 by youssef          ###   ########.fr       */
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

void	draw_minimap2(t_vars *vars, t_vector *pixel,
						t_vector *pos, t_vector *step)
{
	int	x;
	int	y;
	int	color;

	pixel->y = MAP_PADDING;
	pos->y = vars->player.pos.y - (double)MAP_HEIGHT / 2 / BLOCK_SIZE;
	step->y = (vars->player.pos.y - pos->y) / ((double)MAP_HEIGHT / 2);
	x = (int)floor(pos->x);
	if (pos->x < 0)
		x = 0;
	else if (pos->x >= vars->scene.longest)
		x = (int) vars->scene.longest - 1;
	while (pixel->y < MAP_HEIGHT + MAP_PADDING)
	{
		y = (int)floor(pos->y);
		if (pos->y < 0)
			y = 0;
		else if (pos->y >= (int)vars->scene.size)
			y = (int) vars->scene.size - 1;
		color = get_color(vars->scene.minimap[y][x]);
		my_mlx_pixel_put(&vars->image, pixel->x, pixel->y, color);
		pixel->y++;
		pos->y += step->y;
	}
}

void	draw_minimap(t_vars *vars)
{
	t_vector	pixel;
	t_vector	pos;
	t_vector	step;

	pixel.x = MAP_PADDING;
	pos.x = vars->player.pos.x - (double)MAP_WIDTH / BLOCK_SIZE / 2 ;
	step.x = (vars->player.pos.x - pos.x) / ((double)MAP_WIDTH / 2);
	while (pixel.x < MAP_WIDTH + MAP_PADDING)
	{
		draw_minimap2(vars, &pixel, &pos, &step);
		pixel.x++;
		pos.x += step.x;
	}
	pixel.x = MAP_WIDTH / 2 + MAP_PADDING;
	pixel.y = MAP_HEIGHT / 2 + MAP_PADDING;
	draw_square(&vars->image, pixel, 4, RED);
}
