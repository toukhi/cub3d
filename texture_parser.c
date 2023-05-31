/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_parser.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abiru <abiru@student.42abudhabi.ae>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 17:47:58 by abiru             #+#    #+#             */
/*   Updated: 2023/05/31 17:57:57 by abiru            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

bool	validate_texture(t_scene_infn *scene, char **str)
{
	if (str[0] && !ft_strncmp(str[0], "NO", ft_strlen(str[0])))
	{
		if (check_duplicate(scene, 0))
			return (ft_putendl_fd(ERR, 2), ft_putendl_fd(N_DUP, 2), false);
		else if (get_split_size(str) > 2)
			return (ft_putendl_fd(ERR, 2), ft_putendl_fd(N_EXT, 2), false);
		else if (str + 1 && str[1])
		{
			scene->textures[0] = ft_strdup(str[1]);
			scene->counter++;
			scene->is_duplicate[0]++;
		}
		else
			return (ft_putendl_fd(ERR, 2), ft_putendl_fd(N_ERR, 2), false);
	}
	else if (str[0] && !ft_strncmp(str[0], "SO", ft_strlen(str[0])))
	{
		if (check_duplicate(scene, 1))
			return (ft_putendl_fd(ERR, 2), ft_putendl_fd(S_DUP, 2), false);
		else if (get_split_size(str) > 2)
			return (ft_putendl_fd(ERR, 2), ft_putendl_fd(S_EXT, 2), false);
		else if (str + 1 && str[1])
		{
			scene->textures[1] = ft_strdup(str[1]);
			scene->counter++;
			scene->is_duplicate[1]++;
		}
		else
			return (ft_putendl_fd(ERR, 2), ft_putendl_fd(S_ERR, 2), false);
	}
	else if (str[0] && !ft_strncmp(str[0], "WE", ft_strlen(str[0])))
	{
		if (check_duplicate(scene, 2))
			return (ft_putendl_fd(ERR, 2), ft_putendl_fd(W_DUP, 2), false);
		else if (get_split_size(str) > 2)
			return (ft_putendl_fd(ERR, 2), ft_putendl_fd(W_EXT, 2), false);
		else if (str + 1 && str[1])
		{
			scene->textures[2] = ft_strdup(str[1]);
			scene->counter++;
			scene->is_duplicate[2]++;
		}
		else
			return (ft_putendl_fd(ERR, 2), ft_putendl_fd(W_ERR, 2), false);
	}
	else if (str[0] && !ft_strncmp(str[0], "EA", ft_strlen(str[0])))
	{
		if (check_duplicate(scene, 3))
			return (ft_putendl_fd(ERR, 2), ft_putendl_fd(E_DUP, 2), false);
		else if (get_split_size(str) > 2)
			return (ft_putendl_fd(ERR, 2), ft_putendl_fd(E_EXT, 2), false);
		if (str + 1 && str[1])
		{
			scene->textures[3] = ft_strdup(str[1]);
			scene->counter++;
			scene->is_duplicate[3]++;
		}
		else
			return (ft_putendl_fd(ERR, 2), ft_putendl_fd(E_ERR, 2), false);
	}
	return (true);
}
