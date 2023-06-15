/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-touk <yel-touk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 19:21:01 by yel-touk          #+#    #+#             */
/*   Updated: 2023/06/15 20:16:47 by yel-touk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	key_hook(int keycode, t_vars *vars)
{
	printf("Key code: %d\n", keycode);
	if (keycode == ESC)
		quit(vars);
	if (keycode == W || keycode == A || keycode == S || keycode == D)
	{
		//move character
	}
	if (keycode == UP_ARROW || keycode == LEFT_ARROW || keycode == DOWN_ARROW || keycode == RIGHT_ARROW)
	{
		//rotate character
	}
	return (0);
}
