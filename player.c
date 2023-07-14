/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-touk <yel-touk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/14 17:33:51 by yel-touk          #+#    #+#             */
/*   Updated: 2023/07/14 17:57:42 by yel-touk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

bool	is_collision(t_vars *vars, double move_speed, int key)
{
	double	x;
	double	y;

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
	if ((key == W && vars->player.dir.x < 0) || (key == S && vars->player.dir.x >= 0)
		|| (key == A && vars->player.plane.x >= 0) || (key == D && vars->player.plane.x < 0))
		x -= SAFETY_DIST;
	else
		x += SAFETY_DIST;
	if ((key == W && vars->player.dir.y < 0) || (key == S && vars->player.dir.y >= 0)
		|| (key == A && vars->player.plane.y >= 0) || (key == D && vars->player.plane.y < 0))
		y -= SAFETY_DIST;
	else
		y += SAFETY_DIST;
	if (vars->scene.minimap[(int)y][(int)x] != '1')
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
	set_keys(key, &(vars->keys), false);
}

void	*make_sound(void *vars)
{
	t_vars	*l_vars;

	l_vars = (t_vars *)vars;
	while (true)
	{
		pthread_mutex_lock(&l_vars->checker);
		if (!l_vars->screen)
		{
			pthread_mutex_unlock(&l_vars->checker);
			break ;
		}
		if (l_vars->cur_key == B)
			system("afplay mixkit-heavy-sword-hit-2794.wav");
		l_vars->cur_key = -1;
		pthread_mutex_unlock(&l_vars->checker);
		usleep(500);
	}
	return (0);
}
