/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rays.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-touk <yel-touk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 13:32:08 by yel-touk          #+#    #+#             */
/*   Updated: 2023/07/08 21:17:58 by yel-touk         ###   ########.fr       */
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
	double	cameraX;
	t_ray	*ray_p;
	
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
			
		double wallX;
		if ((*ray_p).side == 0 || (*ray_p).side == 2)
			wallX = vars->player.pos.y + (*ray_p).wallDist * (*ray_p).dir.y;
		else
			wallX = vars->player.pos.x + (*ray_p).wallDist * (*ray_p).dir.x;
		wallX -= floor(wallX);
		int texX = 0; // = (int) wallX * (double) vars->scene.
		double step = 0;
		if ((*ray_p).side == 0)
		{
			texX = (int) wallX * (double) vars->scene.WE.width;
			if ((*ray_p).dir.x)
				texX = vars->scene.WE.width - texX - 1;
			step = 1.0 * vars->scene.WE.height / lineHeight;
		}
		if ((*ray_p).side == 1)
		{
			texX = (int) wallX * (double) vars->scene.NO.width;
			if ((*ray_p).dir.x)
				texX = vars->scene.NO.width - texX - 1;
			step = 1.0 * vars->scene.NO.height / lineHeight;
		}
		if ((*ray_p).side == 2)
		{
			texX = (int) wallX * (double) vars->scene.EA.width;
			if ((*ray_p).dir.x)
				texX = vars->scene.EA.width - texX - 1;
			step = 1.0 * vars->scene.EA.height / lineHeight;
		}
		if ((*ray_p).side == 3)
		{
			texX = (int) wallX * (double) vars->scene.SO.width;
			if ((*ray_p).dir.x)
				texX = vars->scene.SO.width - texX - 1;
			step = 1.0 * vars->scene.SO.height / lineHeight;
		}
		double texPos = (drawStart - WIN_HEIGHT / 2 + lineHeight / 2) * step;
		int y = drawStart - 1;
		while (++y < drawEnd)
		{
			 int color = 0;
			int texY = 0;
			if ((*ray_p).side == 0)
			{
				texY = (int)texPos & (vars->scene.WE.height - 1);
				color = *( int *)(vars->scene.WE.img.addr) + (vars->scene.WE.height * texY * vars->scene.WE.img.line_length + texX * (vars->scene.WE.img.bits_per_pixel / 8));
			}
			else if ((*ray_p).side == 1)
			{
				texY = (int)texPos & (vars->scene.NO.height - 1);
				color = *( int *)(vars->scene.NO.img.addr) + (vars->scene.NO.height * texY * vars->scene.NO.img.line_length + texX * (vars->scene.NO.img.bits_per_pixel / 8));
			}
			else if ((*ray_p).side == 2)
			{
				texY = (int)texPos & (vars->scene.EA.height - 1);
				color = *( int *)(vars->scene.EA.img.addr) + (vars->scene.EA.height * texY * vars->scene.EA.img.line_length + texX * (vars->scene.EA.img.bits_per_pixel / 8));
			}
			else if ((*ray_p).side == 3)
			{
				texY = (int)texPos & (vars->scene.SO.height - 1);
				color = *( int *)(vars->scene.SO.img.addr) + (vars->scene.SO.height * texY * vars->scene.SO.img.line_length + texX * (vars->scene.SO.img.bits_per_pixel / 8));
			}
			texPos += step;
			// color = vars->sce.addr + (vars->scene.NO.height * texY * data->line_length + texX * (vars->data.bits_per_pixel / 8));
			my_mlx_pixel_put(&vars->image, ray_num, y, color );
		}
			
        // if ((*ray_p).side == 0)
        //     draw_ver_line(&vars->image, ray_num, drawStart, drawEnd, GRAY);
        // else if ((*ray_p).side == 1)
        //     draw_ver_line(&vars->image, ray_num, drawStart, drawEnd, RED);
		// else if ((*ray_p).side == 2)
        //     draw_ver_line(&vars->image, ray_num, drawStart, drawEnd, CAMEL);
		// else if ((*ray_p).side == 3)
        //     draw_ver_line(&vars->image, ray_num, drawStart, drawEnd, WHITE);
    }
}