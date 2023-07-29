/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youssef <youssef@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/14 17:33:51 by yel-touk          #+#    #+#             */
/*   Updated: 2023/07/29 20:08:29 by youssef          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D_bonus.h"

bool	is_collision_x(t_vars *vars, double move_speed, int key)
{
	double	x;

	x = 0.0;
	if (key == W)
		x = vars->player.pos.x + move_speed * vars->player.dir.x;
	if (key == S)
		x = vars->player.pos.x - move_speed * vars->player.dir.x;
	if (key == A)
		x = vars->player.pos.x - move_speed * vars->player.plane.x;
	if (key == D)
		x = vars->player.pos.x + move_speed * vars->player.plane.x;
	if ((key == W && vars->player.dir.x < 0)
		|| (key == S && vars->player.dir.x >= 0)
		|| (key == A && vars->player.plane.x >= 0)
		|| (key == D && vars->player.plane.x < 0))
		x -= SAFETY_DIST;
	else
		x += SAFETY_DIST;
	if (vars->scene.minimap[(int)vars->player.pos.y][(int)x] != '1')
		return (false);
	return (true);
}

bool	is_collision_y(t_vars *vars, double move_speed, int key)
{
	double	y;

	y = 0.0;
	if (key == W)
		y = vars->player.pos.y + move_speed * vars->player.dir.y;
	if (key == S)
		y = vars->player.pos.y - move_speed * vars->player.dir.y;
	if (key == A)
		y = vars->player.pos.y - move_speed * vars->player.plane.y;
	if (key == D)
		y = vars->player.pos.y + move_speed * vars->player.plane.y;
	if ((key == W && vars->player.dir.y < 0)
		|| (key == S && vars->player.dir.y >= 0)
		|| (key == A && vars->player.plane.y >= 0)
		|| (key == D && vars->player.plane.y < 0))
		y -= SAFETY_DIST;
	else
		y += SAFETY_DIST;
	if (vars->scene.minimap[(int)y][(int)vars->player.pos.x] != '1')
		return (false);
	return (true);
}

void	move_player(t_vars *vars)
{
	double	move_speed;

	if (vars->keys.run)
		move_speed = RUN_SPEED;
	else
		move_speed = WALK_SPEED;
	if (vars->keys.w)
		move_forward(vars, move_speed);
	if (vars->keys.a)
		move_left(vars, move_speed);
	if (vars->keys.s)
		move_backward(vars, move_speed);
	if (vars->keys.d)
		move_right(vars, move_speed);
}

void	rotate_player(t_vector *dir, t_vector *plane, t_keys *keys)
{
	double		angle;
	t_vector	old_dir;
	t_vector	old_plane;

	old_dir = *dir;
	old_plane = *plane;
	angle = 0;
	if (keys->left)
		angle = -TURN_ANGLE;
	if (keys->right)
		angle = TURN_ANGLE;
	(*dir).x = cos(angle) * old_dir.x - sin(angle) * old_dir.y;
	(*dir).y = sin(angle) * old_dir.x + cos(angle) * old_dir.y;
	(*plane).x = cos(angle) * old_plane.x - sin(angle) * old_plane.y;
	(*plane).y = sin(angle) * old_plane.x + cos(angle) * old_plane.y;
}

void	rotate_player_mouse(int key, t_vars *vars)
{
	set_keys(key, &(vars->keys), true);
	rotate_player(&(vars->player.dir), &(vars->player.plane), &(vars->keys));
	rotate_player(&(vars->player.dir), &(vars->player.plane), &(vars->keys));
	set_keys(key, &(vars->keys), false);
}
