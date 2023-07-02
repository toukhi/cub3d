/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youssef <youssef@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 19:21:01 by yel-touk          #+#    #+#             */
/*   Updated: 2023/07/02 17:15:12 by youssef          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	move_player(t_vars *vars, int key)
{
	if (key == W)
	{
		vars->player.pos.x += 0.2 * vars->player.dir.x;
		vars->player.pos.y += 0.2 * vars->player.dir.y;
	}
	if (key == A)
		vars->player.pos.x -= 0.1;
	if (key == S)
	{
		vars->player.pos.x -= 0.2 * vars->player.dir.x;
		vars->player.pos.y -= 0.2 * vars->player.dir.y;
	}
	if (key == D)
		vars->player.pos.x += 0.1;
}

void	rotate_player(t_vector *dir, t_vector *plane, int key)
{
	double		angle;
	t_vector	old_dir;
	t_vector	old_plane;

	old_dir = *dir;
	old_plane = *plane;
	if (key == LEFT_ARROW)
		angle = -TURN_ANGLE;
	if (key == RIGHT_ARROW)
		angle = TURN_ANGLE;
	(*dir).x = cos(angle) * old_dir.x - sin(angle) * old_dir.y;
	(*dir).y = sin(angle) * old_dir.x + cos(angle) * old_dir.y;
	(*plane).x = cos(angle) * old_plane.x - sin(angle) * old_plane.y;
	(*plane).y = sin(angle) * old_plane.x + cos(angle) * old_plane.y;
}

int	key_up_hook(int key, t_vars *vars)
{
	printf("Key code: %d\n", key);
	if (key == ESC)
		quit(vars);
	return (0);
}

int	key_down_hook(int key, t_vars *vars)
{
	printf("Key code: %d\n", key);
	if (key == W || key == A || key == S || key == D)
	{
		move_player(vars, key);
		redraw_image(vars);
	}
	if (key == UP_ARROW || key == LEFT_ARROW || key == DOWN_ARROW || key == RIGHT_ARROW)
	{
		rotate_player(&(vars->player.dir), &(vars->player.plane), key);
		printf("direction vector: x: %f, y:%f\n", vars->player.dir.x, vars->player.dir.y);
		redraw_image(vars);
	}
	return (0);
}
