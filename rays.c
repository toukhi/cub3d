/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rays.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-touk <yel-touk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 13:32:08 by yel-touk          #+#    #+#             */
/*   Updated: 2023/07/08 14:35:56 by yel-touk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void    set_sideDist(t_ray *ray_p, t_player player)
{
    t_ray   ray;

    ray = *ray_p;
    if (ray.dir.x < 0)
	{
		(*ray_p).step.x = -1;
		(*ray_p).sideDist.x = (player.pos.x - ray.mapX) * ray.deltaDist.x;
	}
	else
	{
		(*ray_p).step.x = 1;
		(*ray_p).sideDist.x = (ray.mapX + 1.0 - player.pos.x) * ray.deltaDist.x;
	}
	if (ray.dir.y < 0)
	{
		(*ray_p).step.y = -1;
		(*ray_p).sideDist.y = (player.pos.y - ray.mapY) * ray.deltaDist.y;
	}
	else
	{
		(*ray_p).step.y = 1;
		(*ray_p).sideDist.y = (ray.mapY + 1.0 - player.pos.y) * ray.deltaDist.y;
	}
}

void    dda(t_ray *ray_p, char **map)//, int ray_num)
{
    while ((*ray_p).hit == 0)
	{
		// printf("For ray %d: deltaDX = %f, deltaDY = %f, sideDX = %f, sideDY = %f\n", ray_num, (*ray_p).deltaDist.x, (*ray_p).deltaDist.y, (*ray_p).sideDist.x, (*ray_p).sideDist.y);
		//jump to next map square, either in x-direction, or in y-direction
		if ((*ray_p).sideDist.x < (*ray_p).sideDist.y)
		{
			(*ray_p).sideDist.x += (*ray_p).deltaDist.x;
			(*ray_p).mapX += (*ray_p).step.x;
			if ((*ray_p).step.x < 0)
				(*ray_p).side = 0;
			else
				(*ray_p).side = 2;
		}
		else
		{
			(*ray_p).sideDist.y += (*ray_p).deltaDist.y;
			(*ray_p).mapY += (*ray_p).step.y;
			if ((*ray_p).step.y < 0)
				(*ray_p).side = 1;
			else
				(*ray_p).side = 3;
		}
		//Check if ray has hit a wall
		// printf("current content: %c\n", map[(*ray_p).mapY][(*ray_p).mapX]);
		if (map[(*ray_p).mapY][(*ray_p).mapX] == '1')
		{
			// printf("mapX: %d, mapY: %d\n", (*ray_p).mapX, (*ray_p).mapY);
			(*ray_p).hit = 1;
		}
	}
}

//probably won't need this func
void    draw_ver_line(t_data *data, int x, int y1, int y2, int color)
{
    int y_start;
    int y_end;

    y_start = y1;
    y_end = y2;
    // if (y2 < y1)
    // {
    //     y_start = y2;
    //     y_end = y1;
	// 	printf("enters here (draw_ver_line)\n");
    // }
    while (y_start <= y_end)
    {
        my_mlx_pixel_put(data, x, y_start, color);
        y_start++;
    }
}

void	draw_screen(t_vars *vars)
{
	int		ray_num;
	// int		w;
	double	cameraX;
	t_ray	*ray_p;

	// w = WIN_WIDTH;  //vars->scene.longest;
	// vars->rays = malloc((w + 1) * sizeof(t_ray));
	// if (!vars->rays)
	// 	quit(vars);
	ray_num = -1;
	while (++ray_num < WIN_WIDTH)
	{
		ray_p = &(vars->rays[ray_num]);
		(*ray_p).mapX = (int) vars->player.pos.x;
		(*ray_p).mapY = (int) vars->player.pos.y;
		// printf("mapX: %d, mapY: %d\n", (*ray_p).mapX, (*ray_p).mapY);
		cameraX = 2 * ray_num / (double) WIN_WIDTH - 1;
		(*ray_p).dir.x = vars->player.dir.x + vars->player.plane.x * cameraX;
		(*ray_p).dir.y = vars->player.dir.y + vars->player.plane.y * cameraX;
		//need to check if rayDir is 0!!!
		(*ray_p).deltaDist.x = fabs(1 / (*ray_p).dir.x);
		(*ray_p).deltaDist.y = fabs(1 / (*ray_p).dir.y);
		// printf("For ray %d: deltaDistX = %f, deltaDistY = %f\n", ray_num, (*ray_p).deltaDist.x, vars->rays[ray_num].deltaDist.y);
		// printf("For ray %d: dirX = %f, dirY = %f\n", ray_num, (*ray_p).dir.x, (*ray_p).dir.y);
		(*ray_p).hit = 0;
		set_sideDist(ray_p, vars->player);
		dda(ray_p, vars->scene.content);//, ray_num);
		// printf("For ray %d: deltaDX = %f, deltaDY = %f, sideDX = %f, sideDY = %f\n", ray_num, (*ray_p).deltaDist.x, (*ray_p).deltaDist.y, (*ray_p).sideDist.x, (*ray_p).sideDist.y);
		if ((*ray_p).side == 0 || (*ray_p).side == 2)
			(*ray_p).wallDist = ((*ray_p).sideDist.x - (*ray_p).deltaDist.x);
		else
			(*ray_p).wallDist = ((*ray_p).sideDist.y - (*ray_p).deltaDist.y);
        //Calculate height of line to draw on screen
        int lineHeight = (int)(WIN_HEIGHT / (*ray_p).wallDist);
		// printf("For ray %d: distance to wall is: %f and lineHeight is %d\n\n", ray_num, (*ray_p).wallDist, lineHeight);

        //calculate lowest and highest pixel to fill in current stripe
        int drawStart = -lineHeight / 2 + WIN_HEIGHT / 2;
        if(drawStart < 0)
            drawStart = 0;
		if (drawStart > 0)
			draw_ver_line(&vars->image, ray_num, 0, drawStart - 1, vars->scene.cc);
        int drawEnd = lineHeight / 2 + WIN_HEIGHT / 2;
        if(drawEnd >= WIN_HEIGHT)
            drawEnd = WIN_HEIGHT - 1;
		if (drawEnd < WIN_HEIGHT - 1)
			draw_ver_line(&vars->image, ray_num, drawEnd + 1, WIN_HEIGHT - 1, vars->scene.fc);
        if ((*ray_p).side == 0)
            draw_ver_line(&vars->image, ray_num, drawStart, drawEnd, GRAY);
        else if ((*ray_p).side == 1)
            draw_ver_line(&vars->image, ray_num, drawStart, drawEnd, RED);
		else if ((*ray_p).side == 2)
            draw_ver_line(&vars->image, ray_num, drawStart, drawEnd, CAMEL);
		else if ((*ray_p).side == 3)
            draw_ver_line(&vars->image, ray_num, drawStart, drawEnd, WHITE);
    }
}