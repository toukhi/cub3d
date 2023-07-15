/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youssef <youssef@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/15 23:25:40 by youssef           #+#    #+#             */
/*   Updated: 2023/07/15 23:26:24 by youssef          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	move_forward(t_vars *vars, double move_speed)
{
	if (!is_collision_x(vars, move_speed, W))
		vars->player.pos.x += move_speed * vars->player.dir.x;
	if (!is_collision_y(vars, move_speed, W))
		vars->player.pos.y += move_speed * vars->player.dir.y;
}

void	move_backward(t_vars *vars, double move_speed)
{
	if (!is_collision_x(vars, move_speed, S))
		vars->player.pos.x -= move_speed * vars->player.dir.x;
	if (!is_collision_y(vars, move_speed, S))
		vars->player.pos.y -= move_speed * vars->player.dir.y;
}

void	move_right(t_vars *vars, double move_speed)
{
	if (!is_collision_x(vars, move_speed, D))
		vars->player.pos.x += move_speed * vars->player.plane.x;
	if (!is_collision_y(vars, move_speed, D))
		vars->player.pos.y += move_speed * vars->player.plane.y;
}

void	move_left(t_vars *vars, double move_speed)
{
	if (!is_collision_x(vars, move_speed, A))
		vars->player.pos.x -= move_speed * vars->player.plane.x;
	if (!is_collision_y(vars, move_speed, A))
		vars->player.pos.y -= move_speed * vars->player.plane.y;
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
