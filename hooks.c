/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youssef <youssef@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 19:21:01 by yel-touk          #+#    #+#             */
/*   Updated: 2023/07/03 21:46:14 by youssef          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	move_player(t_vars *vars)//, int key)
{
	if (vars->keys.w)
	{
		vars->player.pos.x += MOVE_SPEED * vars->player.dir.x;
		vars->player.pos.y += MOVE_SPEED * vars->player.dir.y;
	}
	if (vars->keys.a)
		vars->player.pos.x -= 0.1;
	if (vars->keys.s)
	{
		vars->player.pos.x -= MOVE_SPEED * vars->player.dir.x;
		vars->player.pos.y -= MOVE_SPEED * vars->player.dir.y;
	}
	if (vars->keys.d)
		vars->player.pos.x += 0.1;
}

void	rotate_player(t_vector *dir, t_vector *plane, t_keys *keys)//, int key)
{
	double		angle;
	t_vector	old_dir;
	t_vector	old_plane;

	old_dir = *dir;
	old_plane = *plane;
	if (keys->left)
		angle = -TURN_ANGLE;
	if (keys->right)
		angle = TURN_ANGLE;
	(*dir).x = cos(angle) * old_dir.x - sin(angle) * old_dir.y;
	(*dir).y = sin(angle) * old_dir.x + cos(angle) * old_dir.y;
	(*plane).x = cos(angle) * old_plane.x - sin(angle) * old_plane.y;
	(*plane).y = sin(angle) * old_plane.x + cos(angle) * old_plane.y;
}

void	set_keys(int key, t_keys *keys, bool status)
{
	if (key == W)
		keys->w = status;
	if (key == A)
		keys->a = status;
	if (key == S)
		keys->s = status;
	if (key == D)
		keys->d = status;
	if (key == UP_ARROW)
		keys->up = status;
	if (key == LEFT_ARROW)
		keys->left = status;
	if (key == DOWN_ARROW)
		keys->down = status;
	if (key == RIGHT_ARROW)
		keys->right = status;
}

int	key_up_hook(int key, t_vars *vars)
{
	printf("Key code: %d\n", key);
	if (key == ESC)
		quit(vars);
	set_keys(key, &(vars->keys), false);
	return (0);
}

int	key_down_hook(int key, t_vars *vars)
{
	set_keys(key, &(vars->keys), true);
	// printf("Key code: %d\n", key);
	// if (key == W || key == A || key == S || key == D)
	// {
	// 	move_player(vars, key);
	// 	redraw_image(vars);
	// }
	// if (key == UP_ARROW || key == LEFT_ARROW || key == DOWN_ARROW || key == RIGHT_ARROW)
	// {
	// 	rotate_player(&(vars->player.dir), &(vars->player.plane), key);
	// 	printf("direction vector: x: %f, y:%f\n", vars->player.dir.x, vars->player.dir.y);
	// 	redraw_image(vars);
	// }
	return (0);
}

int	update_scene(t_vars *vars)
{
	move_player(vars);
	rotate_player(&(vars->player.dir), &(vars->player.plane), &(vars->keys));
	redraw_image(vars);
	return (0);
}
