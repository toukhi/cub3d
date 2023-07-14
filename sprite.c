/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abiru <abiru@student.42abudhabi.ae>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/14 20:22:31 by abiru             #+#    #+#             */
/*   Updated: 2023/07/14 20:34:12 by abiru            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static bool	check_sprite2(t_vars *vars)
{
	vars->scene.weapon3.img.img = mlx_xpm_file_to_image(&vars->mlx,
			"./textures/knife3.xpm", &vars->scene.weapon3.width,
			&vars->scene.weapon3.height);
	if (!vars->scene.weapon3.img.img)
		return (ft_putendl_fd(ERR, 2), ft_putendl_fd(SPRITE, 2), false);
	vars->scene.weapon3.img.addr
		= mlx_get_data_addr(vars->scene.weapon3.img.img,
			&vars->scene.weapon3.img.bits_per_pixel,
			&vars->scene.weapon3.img.line_length,
			&vars->scene.weapon3.img.endian);
	return (true);
}

bool	check_sprite(t_vars *vars)
{
	vars->scene.weapon1.img.img = mlx_xpm_file_to_image(&vars->mlx,
			"./textures/knife1.xpm", &vars->scene.weapon1.width,
			&vars->scene.weapon1.height);
	if (!vars->scene.weapon1.img.img)
		return (ft_putendl_fd(ERR, 2), ft_putendl_fd(SPRITE, 2), false);
	vars->scene.weapon1.img.addr
		= mlx_get_data_addr(vars->scene.weapon1.img.img,
			&vars->scene.weapon1.img.bits_per_pixel,
			&vars->scene.weapon1.img.line_length,
			&vars->scene.weapon1.img.endian);
	vars->scene.weapon2.img.img = mlx_xpm_file_to_image(&vars->mlx,
			"./textures/knife2.xpm", &vars->scene.weapon2.width,
			&vars->scene.weapon2.height);
	if (!vars->scene.weapon2.img.img)
		return (ft_putendl_fd(ERR, 2), ft_putendl_fd(SPRITE, 2), false);
	vars->scene.weapon2.img.addr
		= mlx_get_data_addr(vars->scene.weapon2.img.img,
			&vars->scene.weapon2.img.bits_per_pixel,
			&vars->scene.weapon2.img.line_length,
			&vars->scene.weapon2.img.endian);
	if (!check_sprite2(vars))
		return (false);
	return (true);
}
