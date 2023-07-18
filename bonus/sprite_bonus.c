/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-touk <yel-touk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/14 20:22:31 by abiru             #+#    #+#             */
/*   Updated: 2023/07/18 18:57:07 by yel-touk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D_bonus.h"

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

static void	set_weapon(t_vars *vars, t_texture *weapon, int *start_x)
{
	if (vars->keys.attack == 1 || vars->keys.attack == 3)
	{
		*weapon = vars->scene.weapon2;
		*start_x -= weapon->width / 2;
	}
	if (vars->keys.attack == 2)
	{
		*weapon = vars->scene.weapon3;
		*start_x -= weapon->width;
	}
	else
		*weapon = vars->scene.weapon1;
}

static void	update_attack_val(t_vars *vars)
{
	if (vars->keys.attack > 0 && vars->keys.attack < 3)
		vars->keys.attack++;
	if (vars->keys.attack == 3)
		vars->keys.attack = 0;
}

void	draw_sprite(t_vars *vars)
{
	t_sp_vars	sp;
	t_texture	weapon;

	sp.tex_x = -1;
	sp.color = 0;
	sp.start_x = WIN_WIDTH / 5 * 3;
	set_weapon(vars, &weapon, &sp.start_x);
	sp.colors = (int *)(weapon.img.addr);
	while (++sp.tex_x < weapon.width)
	{
		sp.start_y = WIN_HEIGHT - weapon.height;
		sp.tex_y = -1;
		while (++sp.tex_y < weapon.height)
		{
			sp.color = sp.colors[((int)(sp.tex_y)
					*weapon.width + (int)sp.tex_x)];
			if (sp.color != -16777216)
				my_mlx_pixel_put(&vars->image, sp.start_x,
					sp.start_y, sp.color);
			sp.start_y++;
		}
		sp.start_x++;
	}
	update_attack_val(vars);
}
