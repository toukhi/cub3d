/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youssef <youssef@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 19:21:01 by yel-touk          #+#    #+#             */
/*   Updated: 2023/06/23 18:23:18 by youssef          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	move_player(t_vars *vars, int key)
{
	if (key == W)
		vars->player.pos.y -= 0.1;
	if (key == A)
		vars->player.pos.x -= 0.1;
	if (key == S)
		vars->player.pos.y += 0.1;
	if (key == D)
		vars->player.pos.x += 0.1;
}

int	key_hook(int key, t_vars *vars)
{
	printf("Key code: %d\n", key);
	if (key == ESC)
		quit(vars);
	if (key == W || key == A || key == S || key == D)
	{
		move_player(vars, key);
		redraw_image(vars);
	}
	if (key == UP_ARROW || key == LEFT_ARROW || key == DOWN_ARROW || key == RIGHT_ARROW)
	{
		//rotate character
	}
	return (0);
}
