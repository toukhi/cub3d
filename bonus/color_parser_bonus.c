/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_parser_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-touk <yel-touk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 17:53:15 by abiru             #+#    #+#             */
/*   Updated: 2023/07/18 18:54:51 by yel-touk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D_bonus.h"

static int	find_clr(int a, int b, int c)
{
	return (a << 16 | b << 8 | c);
}

static bool	get_ind_clrs(char **str, char **tmp, t_scene_infn *scene)
{
	if (get_split_size(tmp) != 3 || check_empty_field(tmp))
		return (ft_putendl_fd(ERR, 2), ft_putendl_fd(EXT_ERR, 2), false);
	if (!ft_strncmp(str[0], "F", ft_strlen(str[0])))
	{
		if (ft_atoi(tmp[0]) == -1 || ft_atoi(tmp[1]) == -1
			|| ft_atoi(tmp[2]) == -1)
			return (ft_putendl_fd(ERR, 2), ft_putendl_fd(F_INV, 2), false);
		scene->fc = find_clr(ft_atoi(tmp[0]), ft_atoi(tmp[1]), ft_atoi(tmp[2]));
		scene->is_duplicate[5]++;
	}
	else
	{
		if (ft_atoi(tmp[0]) == -1 || ft_atoi(tmp[1]) == -1
			|| ft_atoi(tmp[2]) == -1)
			return (ft_putendl_fd(ERR, 2), ft_putendl_fd(C_INV, 2), false);
		scene->cc = find_clr(ft_atoi(tmp[0]), ft_atoi(tmp[1]), ft_atoi(tmp[2]));
		scene->is_duplicate[4]++;
	}
	scene->counter++;
	return (true);
}

static bool	get_colors2(char *tmp2, char **str, t_scene_infn *scene)
{
	char	**tmp;

	tmp = ft_ssplit(tmp2, ",");
	free(tmp2);
	if (tmp)
	{
		if (!get_ind_clrs(str, tmp, scene))
			return (free_split(tmp), false);
		free_split(tmp);
		return (true);
	}
	return (false);
}

size_t	get_char_count(char *str, unsigned char c)
{
	size_t	i;
	size_t	count;

	i = 0;
	count = 0;
	if (!str || !c)
		return (0);
	while (str[i])
	{
		if (str[i] == c)
			count++;
		i++;
	}
	return (count);
}

bool	get_colors(t_scene_infn *scene, char **str, char *val)
{
	char	*tmp2;

	if (!ft_strncmp(str[0], "C", ft_strlen(str[0]))
		|| !ft_strncmp(str[0], "F", ft_strlen(str[0])))
	{
		if (str[1])
		{
			tmp2 = ft_strtrim(val + 1, " \t\r\v\f\n");
			if (get_char_count(tmp2, ',') != 2)
				return (free(tmp2), ft_putendl_fd(ERR, 2),
					ft_putendl_fd(INV_COMMA, 2), false);
			if (!get_colors2(tmp2, str, scene))
				return (false);
		}
		else
			return (ft_putendl_fd(ERR, 2), ft_putendl_fd(C_ABS, 2), false);
	}
	return (true);
}
