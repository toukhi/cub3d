/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rays.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-touk <yel-touk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 13:32:08 by yel-touk          #+#    #+#             */
/*   Updated: 2023/07/15 16:27:07 by yel-touk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	set_side_dist(t_ray *ray_p, t_player p)
{
	t_ray	ray;

	ray = *ray_p;
	if (ray.dir.x < 0)
	{
		(*ray_p).step.x = -1;
		(*ray_p).side_dist.x = (p.pos.x - ray.map_x) * ray.delta_dist.x;
	}
	else
	{
		(*ray_p).step.x = 1;
		(*ray_p).side_dist.x = (ray.map_x + 1.0 - p.pos.x) * ray.delta_dist.x;
	}
	if (ray.dir.y < 0)
	{
		(*ray_p).step.y = -1;
		(*ray_p).side_dist.y = (p.pos.y - ray.map_y) * ray.delta_dist.y;
	}
	else
	{
		(*ray_p).step.y = 1;
		(*ray_p).side_dist.y = (ray.map_y + 1.0 - p.pos.y) * ray.delta_dist.y;
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

void	set_texture(t_ray **ray_p, t_vars *vars)
{
	if ((*ray_p)->side == 0)
		(*ray_p)->texture = vars->scene.we;
	if ((*ray_p)->side == 1)
		(*ray_p)->texture = vars->scene.no;
	if ((*ray_p)->side == 2)
		(*ray_p)->texture = vars->scene.ea;
	if ((*ray_p)->side == 3)
		(*ray_p)->texture = vars->scene.so;
}

void	set_wall_x(t_ray **ray_p, t_vars *vars)
{
	if ((*ray_p)->side == 0 || (*ray_p)->side == 2)
		(*ray_p)->wall_x = vars->player.pos.y
			+ (*ray_p)->wall_dist * (*ray_p)->dir.y;
	else
		(*ray_p)->wall_x = vars->player.pos.x
			+ (*ray_p)->wall_dist * (*ray_p)->dir.x;
	(*ray_p)->wall_x -= floor((*ray_p)->wall_x);
}
