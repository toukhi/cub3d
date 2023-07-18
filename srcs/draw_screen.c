/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_screen.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-touk <yel-touk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/15 16:25:02 by yel-touk          #+#    #+#             */
/*   Updated: 2023/07/15 16:30:23 by yel-touk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	dda(t_ray *ray_p, char **map)
{
	while ((*ray_p).hit == 0)
	{
		if ((*ray_p).side_dist.x < (*ray_p).side_dist.y)
		{
			(*ray_p).side_dist.x += (*ray_p).delta_dist.x;
			(*ray_p).map_x += (*ray_p).step.x;
			if ((*ray_p).step.x < 0)
				(*ray_p).side = 0;
			else
				(*ray_p).side = 2;
		}
		else
		{
			(*ray_p).side_dist.y += (*ray_p).delta_dist.y;
			(*ray_p).map_y += (*ray_p).step.y;
			if ((*ray_p).step.y < 0)
				(*ray_p).side = 1;
			else
				(*ray_p).side = 3;
		}
		if (map[(*ray_p).map_y][(*ray_p).map_x] == '1')
		{
			(*ray_p).hit = 1;
		}
	}
}

void	draw_ver_line(t_data *data, int x, t_vector y, int color)
{
	int	y_start;
	int	y_end;

	y_start = y.x;
	y_end = y.y;
	while (y_start <= y_end)
	{
		my_mlx_pixel_put(data, x, y_start, color);
		y_start++;
	}
}

void	draw_background(t_ray **ray_p, t_vars *vars,
	int wall_height, int ray_num)
{
	(*ray_p)->draw_start = -wall_height / 2 + WIN_HEIGHT / 2;
	if ((*ray_p)->draw_start < 0)
		(*ray_p)->draw_start = 0;
	if ((*ray_p)->draw_start > 0)
		draw_ver_line(&vars->image, ray_num,
			(t_vector){0, (*ray_p)->draw_start - 1}, vars->scene.cc);
	(*ray_p)->draw_end = wall_height / 2 + WIN_HEIGHT / 2;
	if ((*ray_p)->draw_end >= WIN_HEIGHT)
		(*ray_p)->draw_end = WIN_HEIGHT - 1;
	if ((*ray_p)->draw_end < WIN_HEIGHT - 1)
		draw_ver_line(&vars->image, ray_num, (t_vector){(*ray_p)->draw_end + 1,
			WIN_HEIGHT - 1}, vars->scene.fc);
}

void	draw_wall(t_ray *ray_p, t_vars *vars, int pixel_x, int wall_height)
{
	t_vector	texture;
	double		step;
	double		tex_pos;
	int			pixel_y;
	int			*colors;

	texture.x = (int)((*ray_p).wall_x * (double)((*ray_p).texture.width));
	if (((*ray_p).side == 0 || (*ray_p).side == 2) && (*ray_p).dir.x > 0)
		texture.x = (*ray_p).texture.width - texture.x - 1;
	if (((*ray_p).side == 1 || (*ray_p).side == 3) && (*ray_p).dir.y < 0)
		texture.x = (*ray_p).texture.width - texture.x - 1;
	step = 1.0 * (*ray_p).texture.height / wall_height;
	tex_pos = ((*ray_p).draw_start - WIN_HEIGHT / 2 + wall_height / 2) * step;
	pixel_y = (*ray_p).draw_start - 1;
	colors = (int *)((*ray_p).texture.img.addr);
	while (++pixel_y < (*ray_p).draw_end)
	{
		texture.y = (int)tex_pos & ((*ray_p).texture.height - 1);
		tex_pos += step;
		my_mlx_pixel_put(&vars->image, pixel_x, pixel_y,
			colors[(((int)(texture.y)) * (*ray_p).texture.width
				+ (int)texture.x)]);
	}
}

void	draw_screen(t_vars *vars)
{
	int		ray_num;
	t_ray	*ray_p;
	int		wall_height;

	ray_num = -1;
	while (++ray_num < WIN_WIDTH)
	{
		set_ray_p(&ray_p, ray_num, vars);
		set_side_dist(ray_p, vars->player);
		dda(ray_p, vars->scene.content);
		set_wall_dist(&ray_p);
		wall_height = (int)(WIN_HEIGHT / (*ray_p).wall_dist);
		draw_background(&ray_p, vars, wall_height, ray_num);
		set_wall_x(&ray_p, vars);
		set_texture(&ray_p, vars);
		draw_wall(ray_p, vars, ray_num, wall_height);
	}
	draw_sprite(vars);
}
