/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-touk <yel-touk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 19:21:01 by yel-touk          #+#    #+#             */
/*   Updated: 2023/06/15 19:46:48 by yel-touk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	key_hook(int keycode, t_vars *vars)
{
	printf("Key code: %d\n", keycode);
	if (keycode == 53)
		quit(vars);
	if (keycode == 13 || keycode == 0 || keycode == 1 || keycode == 2)
	{
		//move character
	}
	if (keycode == 126 || keycode == 123 || keycode == 125 || keycode == 124)
	{
		//rotate character
	}
	return (0);
}
