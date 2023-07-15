/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rays.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youssef <youssef@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 13:32:08 by yel-touk          #+#    #+#             */
/*   Updated: 2023/07/15 02:18:22 by youssef          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	set_side_dist(t_ray *ray_p, t_player player)
{
	t_ray	ray;

	ray = *ray_p;
	if (ray.dir.x < 0)
	{
		(*ray_p).step.x = -1;
		(*ray_p).side_dist.x = (player.pos.x - ray.map_x) * ray.delta_dist.x;
	}
	else
	{
		(*ray_p).step.x = 1;
		(*ray_p).side_dist.x = (ray.map_x + 1.0 - player.pos.x) * ray.delta_dist.x;
	}
	if (ray.dir.y < 0)
	{
		(*ray_p).step.y = -1;
		(*ray_p).side_dist.y = (player.pos.y - ray.map_y) * ray.delta_dist.y;
	}
	else
	{
		(*ray_p).step.y = 1;
		(*ray_p).side_dist.y = (ray.map_y + 1.0 - player.pos.y) * ray.delta_dist.y;
	}
}

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

void	set_ray_p(t_ray **ray_p, int ray_num, t_vars *vars)
{
	double	camera_x;

	*ray_p = &(vars->rays[ray_num]);
	(**ray_p).map_x = (int) vars->player.pos.x;
	(**ray_p).map_y = (int) vars->player.pos.y;
	camera_x = 2 * ray_num / (double) WIN_WIDTH - 1;
	(**ray_p).dir.x = vars->player.dir.x + vars->player.plane.x * camera_x;
	(**ray_p).dir.y = vars->player.dir.y + vars->player.plane.y * camera_x;
	(**ray_p).delta_dist.x = fabs(1 / (**ray_p).dir.x);
	(**ray_p).delta_dist.y = fabs(1 / (**ray_p).dir.y);
	(**ray_p).hit = 0;
}

void	set_wall_dist(t_ray **ray_p)
{
	if ((**ray_p).side == 0 || (**ray_p).side == 2)
		(**ray_p).wall_dist = ((**ray_p).side_dist.x - (**ray_p).delta_dist.x);
	else
		(**ray_p).wall_dist = ((**ray_p).side_dist.y - (**ray_p).delta_dist.y);
}

// void	draw_wall(t_texture texture, int draw_start, int draw_end, t_vars *vars)
// {
// 	// double	step;
// 	// double	tex_pos;
// 	int	y;
// 	int	*colors;

// 	// step = 1.0 * texture.height / wall_height;
// 	// tex_pos = (draw_start - WIN_HEIGHT / 2 + wall_height / 2) * step;
// 	y = draw_start - 1;
// 	colors = (int *)(texture.img.addr);
// 	while (++y < draw_end)
// 		{
// 			int color = 0;
// 			int texY = 0;
// 			texY = (int)texPos & (texture.height - 1);
// 			texPos += step;
// 			color = colors[((int)(texY) * texture.width + (int)texX)];
// 			my_mlx_pixel_put(&vars->image, ray_num, y, color );
// 		}
// }

void	draw_screen(t_vars *vars)
{
	int		ray_num;
	t_ray	*ray_p;
	int		wall_height;
	int		draw_start;
	int		draw_end;

	ray_num = -1;
	while (++ray_num < WIN_WIDTH)
	{
		set_ray_p(&ray_p, ray_num, vars);
		set_side_dist(ray_p, vars->player);
		dda(ray_p, vars->scene.content);
		set_wall_dist(&ray_p);
		wall_height = (int)(WIN_HEIGHT / (*ray_p).wall_dist);
		draw_start = -wall_height / 2 + WIN_HEIGHT / 2;
		if (draw_start < 0)
			draw_start = 0;
		if (draw_start > 0)
			draw_ver_line(&vars->image, ray_num, (t_vector){0, draw_start - 1}, vars->scene.cc);
		draw_end = wall_height / 2 + WIN_HEIGHT / 2;
		if (draw_end >= WIN_HEIGHT)
			draw_end = WIN_HEIGHT - 1;
		if (draw_end < WIN_HEIGHT - 1)
			draw_ver_line(&vars->image, ray_num, (t_vector){draw_end + 1, WIN_HEIGHT - 1}, vars->scene.fc);
		double wallX;
		t_texture	texture;
		if ((*ray_p).side == 0 || (*ray_p).side == 2)
			wallX = vars->player.pos.y + (*ray_p).wall_dist * (*ray_p).dir.y;
		else
			wallX = vars->player.pos.x + (*ray_p).wall_dist * (*ray_p).dir.x;
		wallX -= floor(wallX);
		int texX = 0;
		double step = 0;
		if ((*ray_p).side == 0)
			texture = vars->scene.we;
		if ((*ray_p).side == 1)
			texture = vars->scene.no;
		if ((*ray_p).side == 2)
			texture = vars->scene.ea;
		if ((*ray_p).side == 3)
			texture = vars->scene.so;
		texX = (int)(wallX * (double)(texture.width));
		if (((*ray_p).side == 0 || (*ray_p).side == 2) && (*ray_p).dir.x > 0)
			texX = texture.width - texX - 1;
		if (((*ray_p).side == 1 || (*ray_p).side == 3) && (*ray_p).dir.y < 0)
			texX = texture.width - texX - 1;
		// draw_wall();
		step = 1.0 * texture.height / wall_height;
		double texPos = (draw_start - WIN_HEIGHT / 2 + wall_height / 2) * step;
		int y = draw_start - 1;
		int	*colors;
		colors = (int *)(texture.img.addr);
		while (++y < draw_end)
		{
			int color = 0;
			int texY = 0;
			texY = (int)texPos & (texture.height - 1);
			texPos += step;
			color = colors[((int)(texY) * texture.width + (int)texX)];
			my_mlx_pixel_put(&vars->image, ray_num, y, color);
		}
	}
	draw_sprite(vars);
}
