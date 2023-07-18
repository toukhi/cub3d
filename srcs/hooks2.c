/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youssef <youssef@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 01:17:16 by youssef           #+#    #+#             */
/*   Updated: 2023/07/18 01:17:38 by youssef          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	update_scene(t_vars *vars)
{
	move_player(vars);
	rotate_player(&(vars->player.dir), &(vars->player.plane), &(vars->keys));
	redraw_image(vars);
	return (0);
}
