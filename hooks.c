/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-touk <yel-touk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 19:21:01 by yel-touk          #+#    #+#             */
/*   Updated: 2023/07/05 13:28:10 by yel-touk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

bool	is_collision(t_vars *vars, double move_speed, int key)
{
	int	x;
	int	y;

	if (key == W)
	{
		x = vars->player.pos.x + move_speed * vars->player.dir.x;
		y = vars->player.pos.y + move_speed * vars->player.dir.y;
	}
	if (key == S)
	{
		x = vars->player.pos.x - move_speed * vars->player.dir.x;
		y = vars->player.pos.y - move_speed * vars->player.dir.y;
	}
	if (key == A)
	{
		x = vars->player.pos.x - move_speed * vars->player.plane.x;
		y = vars->player.pos.y - move_speed * vars->player.plane.y;
	}
	if (key == D)
	{
		x = vars->player.pos.x + move_speed * vars->player.plane.x;
		y = vars->player.pos.y + move_speed * vars->player.plane.y;
	}
	printf("minimap next step for x: %d, y: %d, value: %c\n", x, y, vars->scene.minimap[y][x]);
	if (vars->scene.minimap[y][x] != '1')
		return (false);
	return (true);
}

void	move_player(t_vars *vars)//, int key)
{
	double move_speed;

	if (vars->keys.r)
		move_speed = RUN_SPEED;
	else
		move_speed = WALK_SPEED;
	if (vars->keys.w && !is_collision(vars, move_speed, W))
	{
		vars->player.pos.x += move_speed * vars->player.dir.x;
		vars->player.pos.y += move_speed * vars->player.dir.y;
	}
	if (vars->keys.a && !is_collision(vars, move_speed, A))
	{
		vars->player.pos.x -= move_speed * vars->player.plane.x;
		vars->player.pos.y -= move_speed * vars->player.plane.y;	
	}
	if (vars->keys.s && !is_collision(vars, move_speed, S))
	{
		vars->player.pos.x -= move_speed * vars->player.dir.x;
		vars->player.pos.y -= move_speed * vars->player.dir.y;
	}
	if (vars->keys.d && !is_collision(vars, move_speed, D))
	{
		vars->player.pos.x += move_speed * vars->player.plane.x;
		vars->player.pos.y += move_speed * vars->player.plane.y;
	}
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
	if (key == R)
		keys->r = status;
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
