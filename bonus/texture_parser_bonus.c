/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_parser_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-touk <yel-touk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 17:47:58 by abiru             #+#    #+#             */
/*   Updated: 2023/07/18 18:57:10 by yel-touk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D_bonus.h"

static bool	check_north(t_vars *vars, char **str)
{
	if (check_duplicate(&vars->scene, 0))
		return (ft_putendl_fd(ERR, 2), ft_putendl_fd(N_DUP, 2), false);
	else if (get_split_size(str) > 2)
		return (ft_putendl_fd(ERR, 2), ft_putendl_fd(N_EXT, 2), false);
	else if (str[1])
	{
		if (ft_strlen(str[1]) < 4
			|| ft_strcmp(str[1] + ft_strlen(str[1]) - 4, ".xpm"))
			return (ft_putendl_fd(ERR, 2), ft_putendl_fd(N_INEXT, 2), false);
		if (check_texture(str[1], "On North texture -> "))
			return (false);
		update_values(vars, 0, str);
		vars->scene.no.img.img = mlx_xpm_file_to_image(&vars->mlx,
				vars->scene.textures[0], &vars->scene.no.width,
				&vars->scene.no.height);
		if (!vars->scene.no.img.img)
			return (ft_putendl_fd(ERR, 2), ft_putendl_fd(XPM, 2), false);
		vars->scene.no.img.addr = mlx_get_data_addr(vars->scene.no.img.img,
				&vars->scene.no.img.bits_per_pixel,
				&vars->scene.no.img.line_length, &vars->scene.no.img.endian);
		return (true);
	}
	else
		return (ft_putendl_fd(ERR, 2), ft_putendl_fd(N_ERR, 2), false);
}

static bool	check_south(t_vars *vars, char **str)
{
	if (check_duplicate(&vars->scene, 1))
		return (ft_putendl_fd(ERR, 2), ft_putendl_fd(S_DUP, 2), false);
	else if (get_split_size(str) > 2)
		return (ft_putendl_fd(ERR, 2), ft_putendl_fd(S_EXT, 2), false);
	else if (str[1])
	{
		if (ft_strlen(str[1]) < 4
			|| ft_strcmp(str[1] + ft_strlen(str[1]) - 4, ".xpm"))
			return (ft_putendl_fd(ERR, 2), ft_putendl_fd(S_INEXT, 2), false);
		if (check_texture(str[1], "On South texture -> "))
			return (false);
		update_values(vars, 1, str);
		vars->scene.so.img.img = mlx_xpm_file_to_image(&vars->mlx,
				vars->scene.textures[1], &vars->scene.so.width,
				&vars->scene.so.height);
		if (!vars->scene.so.img.img)
			return (ft_putendl_fd(ERR, 2), ft_putendl_fd(XPM, 2), false);
		vars->scene.so.img.addr = mlx_get_data_addr(vars->scene.so.img.img,
				&vars->scene.so.img.bits_per_pixel,
				&vars->scene.so.img.line_length, &vars->scene.so.img.endian);
		return (true);
	}
	else
		return (ft_putendl_fd(ERR, 2), ft_putendl_fd(S_ERR, 2), false);
}

static bool	check_west(t_vars *vars, char **str)
{
	if (check_duplicate(&vars->scene, 2))
		return (ft_putendl_fd(ERR, 2), ft_putendl_fd(W_DUP, 2), false);
	else if (get_split_size(str) > 2)
		return (ft_putendl_fd(ERR, 2), ft_putendl_fd(W_EXT, 2), false);
	else if (str[1])
	{
		if (ft_strlen(str[1]) < 4
			|| ft_strcmp(str[1] + ft_strlen(str[1]) - 4, ".xpm"))
			return (ft_putendl_fd(ERR, 2), ft_putendl_fd(W_INEXT, 2), false);
		if (check_texture(str[1], "On West texture -> "))
			return (false);
		update_values(vars, 2, str);
		vars->scene.we.img.img = mlx_xpm_file_to_image(&vars->mlx,
				vars->scene.textures[2], &vars->scene.we.width,
				&vars->scene.we.height);
		if (!vars->scene.we.img.img)
			return (ft_putendl_fd(ERR, 2), ft_putendl_fd(XPM, 2), false);
		vars->scene.we.img.addr = mlx_get_data_addr(vars->scene.we.img.img,
				&vars->scene.we.img.bits_per_pixel,
				&vars->scene.we.img.line_length, &vars->scene.we.img.endian);
		return (true);
	}
	else
		return (ft_putendl_fd(ERR, 2), ft_putendl_fd(W_ERR, 2), false);
}

static bool	check_east(t_vars *vars, char **str)
{
	if (check_duplicate(&vars->scene, 3))
		return (ft_putendl_fd(ERR, 2), ft_putendl_fd(E_DUP, 2), false);
	else if (get_split_size(str) > 2)
		return (ft_putendl_fd(ERR, 2), ft_putendl_fd(E_EXT, 2), false);
	if (str[1])
	{
		if (ft_strlen(str[1]) < 4
			|| ft_strcmp(str[1] + ft_strlen(str[1]) - 4, ".xpm"))
			return (ft_putendl_fd(ERR, 2), ft_putendl_fd(E_INEXT, 2), false);
		if (check_texture(str[1], "On East texture -> "))
			return (false);
		update_values(vars, 3, str);
		vars->scene.ea.img.img = mlx_xpm_file_to_image(&vars->mlx,
				vars->scene.textures[3], &vars->scene.ea.width,
				&vars->scene.ea.height);
		if (!vars->scene.ea.img.img)
			return (ft_putendl_fd(ERR, 2), ft_putendl_fd(XPM, 2), false);
		vars->scene.ea.img.addr = mlx_get_data_addr(vars->scene.ea.img.img,
				&vars->scene.ea.img.bits_per_pixel,
				&vars->scene.ea.img.line_length, &vars->scene.ea.img.endian);
		return (true);
	}
	else
		return (ft_putendl_fd(ERR, 2), ft_putendl_fd(E_ERR, 2), false);
}

bool	validate_texture(t_vars *vars, char **str)
{
	if (str[0] && !ft_strcmp(str[0], "NO"))
	{
		if (!check_north(vars, str))
			return (false);
	}
	else if (str[0] && !ft_strcmp(str[0], "SO"))
	{
		if (!check_south(vars, str))
			return (false);
	}
	else if (str[0] && !ft_strcmp(str[0], "WE"))
	{
		if (!check_west(vars, str))
			return (false);
	}
	else if (str[0] && !ft_strcmp(str[0], "EA"))
		if (!check_east(vars, str))
			return (false);
	return (true);
}
