/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youssef <youssef@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 19:21:01 by yel-touk          #+#    #+#             */
/*   Updated: 2023/07/16 18:07:49 by youssef          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

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
	if (key == R)
		keys->run = status;
}

int	key_up_hook(int key, t_vars *vars)
{
	pthread_mutex_lock(&vars->checker);
	vars->cur_key = key;
	pthread_mutex_unlock(&vars->checker);
	if (key == ESC)
	{
		pthread_mutex_lock(&vars->checker);
		vars->screen = false;
		pthread_mutex_unlock(&vars->checker);
		quit(vars);
	}
	if (key == X)
		vars->keys.mouse = !vars->keys.mouse;
	if (key == M)
		vars->keys.map = !vars->keys.map;
	if (key == B)
	{
		vars->keys.attack = 1;
	}
	set_keys(key, &(vars->keys), false);
	return (0);
}

int	key_down_hook(int key, t_vars *vars)
{
	set_keys(key, &(vars->keys), true);
	return (0);
}

int	mouse_move_hook(int x, int y, t_vars *vars)
{
	if (vars->keys.mouse)
	{
		if (x < WIN_WIDTH / 3 && x >= 0)
			set_keys(LEFT_ARROW, &(vars->keys), true);
		else if (x > WIN_WIDTH / 3 * 2 && x <= WIN_WIDTH)
			set_keys(RIGHT_ARROW, &(vars->keys), true);
		else
		{
			set_keys(LEFT_ARROW, &(vars->keys), false);
			set_keys(RIGHT_ARROW, &(vars->keys), false);
			if (vars->mouse_pos.x < x)
				rotate_player_mouse(RIGHT_ARROW, vars);
			if (vars->mouse_pos.x > x)
				rotate_player_mouse(LEFT_ARROW, vars);
		}
	}
	vars->mouse_pos.x = x;
	vars->mouse_pos.y = y;
	return (0);
}

int	update_scene(t_vars *vars)
{
	move_player(vars);
	rotate_player(&(vars->player.dir), &(vars->player.plane), &(vars->keys));
	redraw_image(vars);
	return (0);
}
