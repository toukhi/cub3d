/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_parser.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youssef <youssef@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 17:47:58 by abiru             #+#    #+#             */
/*   Updated: 2023/07/08 15:22:34 by youssef          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

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
		vars->scene.textures[0] = ft_strdup(str[1]);
		vars->scene.counter++;
		vars->scene.is_duplicate[0]++;
		vars->scene.NO.img = mlx_xpm_file_to_image(&vars->mlx, vars->scene.textures[0], &vars->scene.NO.width, &vars->scene.NO.height);
		if (!vars->scene.NO.img)
			return (ft_putendl_fd(ERR, 2), ft_putendl_fd(XPM, 2), false);
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
		vars->scene.textures[1] = ft_strdup(str[1]);
		vars->scene.counter++;
		vars->scene.is_duplicate[1]++;
		vars->scene.SO.img = mlx_xpm_file_to_image(&vars->mlx, vars->scene.textures[0], &vars->scene.NO.width, &vars->scene.NO.height);
		if (!vars->scene.SO.img)
			return (ft_putendl_fd(ERR, 2), ft_putendl_fd(XPM, 2), false);
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
		vars->scene.textures[2] = ft_strdup(str[1]);
		vars->scene.counter++;
		vars->scene.is_duplicate[2]++;
		vars->scene.WE.img = mlx_xpm_file_to_image(&vars->mlx, vars->scene.textures[0], &vars->scene.NO.width, &vars->scene.NO.height);
		if (!vars->scene.WE.img)
			return (ft_putendl_fd(ERR, 2), ft_putendl_fd(XPM, 2), false);
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
		vars->scene.textures[3] = ft_strdup(str[1]);
		vars->scene.counter++;
		vars->scene.is_duplicate[3]++;
		vars->scene.EA.img = mlx_xpm_file_to_image(&vars->mlx, vars->scene.textures[0], &vars->scene.NO.width, &vars->scene.NO.height);
		if (!vars->scene.EA.img)
			return (ft_putendl_fd(ERR, 2), ft_putendl_fd(XPM, 2), false);
		return (true);
	}
	else
		return (ft_putendl_fd(ERR, 2), ft_putendl_fd(E_ERR, 2), false);
}

bool	validate_texture(t_vars *vars, char **str)
{
	if (str[0] && !ft_strncmp(str[0], "NO", ft_strlen(str[0])))
	{
		if (!check_north(vars, str))
			return (false);
	}
	else if (str[0] && !ft_strncmp(str[0], "SO", ft_strlen(str[0])))
	{
		if (!check_south(vars, str))
			return (false);
	}
	else if (str[0] && !ft_strncmp(str[0], "WE", ft_strlen(str[0])))
	{
		if (!check_west(vars, str))
			return (false);
	}
	else if (str[0] && !ft_strncmp(str[0], "EA", ft_strlen(str[0])))
		if (!check_east(vars, str))
			return (false);
	return (true);
}
