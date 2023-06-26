/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rays.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-touk <yel-touk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 13:32:08 by yel-touk          #+#    #+#             */
/*   Updated: 2023/06/26 14:07:13 by yel-touk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	init_rays(t_vars *vars)
{
	int		ray_num;
	int		w;
	double	cameraX;
	t_ray	current_ray;

	w = vars->scene.longest;
	vars->rays = malloc((w + 1) * sizeof(t_ray));
	if (!vars->rays)
		quit(vars);
	ray_num = -1;
	while (++ray_num <= w)
	{
		current_ray = vars->rays[ray_num];
		current_ray.mapX = (int) vars->player.pos.x;
		current_ray.mapY = (int) vars->player.pos.y;
		// printf("mapX: %d, mapY: %d\n", current_ray.mapX, current_ray.mapY);
		cameraX = 2 * ray_num / (double) w - 1;
		current_ray.dir.x = vars->player.dir.x + vars->player.plane.x * cameraX;
		current_ray.dir.y = vars->player.dir.y + vars->player.plane.y * cameraX;
		//need to check if rayDir is 0!!
		current_ray.deltaDist.x = fabs(1 / current_ray.dir.x);
		current_ray.deltaDist.y = fabs(1 / current_ray.dir.y);
		// printf("For ray %d: deltaDistX = %f, deltaDistY = %f\n", ray_num, current_ray.deltaDist.x, vars->rays[ray_num].deltaDist.y);
		// printf("For ray %d: dirX = %f, dirY = %f\n", ray_num, current_ray.dir.x, current_ray.dir.y);
		current_ray.hit = 0;
		if (current_ray.dir.x < 0)
		{
			current_ray.step.x = -1;
			current_ray.sideDist.x = (vars->player.pos.x - current_ray.mapX) * current_ray.deltaDist.x;
		}
		else
		{
			current_ray.step.x = 1;
			current_ray.sideDist.x = (current_ray.mapX + 1.0 - vars->player.pos.x) * current_ray.deltaDist.x;
		}
		if (current_ray.dir.y < 0)
		{
			current_ray.step.y = -1;
			current_ray.sideDist.y = (vars->player.pos.y - current_ray.mapY) * current_ray.deltaDist.y;
		}
		else
		{
			current_ray.step.y = 1;
			current_ray.sideDist.y = (current_ray.mapY + 1.0 - vars->player.pos.y) * current_ray.deltaDist.y;
		}
		while (current_ray.hit == 0)
		{
			printf("For ray %d: deltaDX = %f, deltaDY = %f, sideDX = %f, sideDY = %f\n", ray_num, current_ray.deltaDist.x, current_ray.deltaDist.y, current_ray.sideDist.x, current_ray.sideDist.y);
			//jump to next map square, either in x-direction, or in y-direction
			if (current_ray.sideDist.x < current_ray.sideDist.y)
			{
				current_ray.sideDist.x += current_ray.deltaDist.x;
				current_ray.mapX += current_ray.step.x;
				current_ray.side = 0;
			}
			else
			{
				current_ray.sideDist.y += current_ray.deltaDist.y;
				current_ray.mapY += current_ray.step.y;
				current_ray.side = 0;
			}
			//Check if ray has hit a wall
			// printf("current content: %c\n", vars->scene.content[current_ray.mapY][current_ray.mapX]);
			if (vars->scene.content[current_ray.mapY][current_ray.mapX] > '0')
			{
				printf("mapX: %d, mapY: %d\n", current_ray.mapX, current_ray.mapY);
				current_ray.hit = 1;
			}
		}
		printf("For ray %d: deltaDX = %f, deltaDY = %f, sideDX = %f, sideDY = %f\n", ray_num, current_ray.deltaDist.x, current_ray.deltaDist.y, current_ray.sideDist.x, current_ray.sideDist.y);
	}
	// printf("longest: %d\n", w);
}