/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks2_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-touk <yel-touk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 01:17:16 by youssef           #+#    #+#             */
/*   Updated: 2023/07/18 18:56:27 by yel-touk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D_bonus.h"

int	update_scene(t_vars *vars)
{
	move_player(vars);
	rotate_player(&(vars->player.dir), &(vars->player.plane), &(vars->keys));
	redraw_image(vars);
	return (0);
}
