/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_parser.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abiru <abiru@student.42abudhabi.ae>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 17:53:15 by abiru             #+#    #+#             */
/*   Updated: 2023/06/15 20:27:37 by abiru            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	set_longest_line(t_scene_infn *scene)
{
	size_t	i;

	i = 0;
	while (i < scene->size)
	{
		if (ft_strlen(scene->content[i]) > scene->longest)
			scene->longest = ft_strlen(scene->content[i]);
		i++;
	}
}

static int	find_clr(int a, int b, int c)
{
	return (a << 24 | b << 16 | c << 8);
}

static bool	get_ind_clrs(char **str, char **tmp, t_scene_infn *scene)
{
	if (get_split_size(tmp) != 3 || check_empty_field(tmp))
		return (ft_putendl_fd(ERR, 2), ft_putendl_fd(EXT_ERR, 2),
			free_split(tmp), false);
	if (!ft_strncmp(str[0], "F", ft_strlen(str[0])))
	{
		if (ft_atoi(tmp[0]) == -1 || ft_atoi(tmp[1]) == -1
			|| ft_atoi(tmp[2]) == -1)
			return (ft_putendl_fd(ERR, 2), ft_putendl_fd(F_INV, 2),
				free_split(tmp), false);
		scene->fc = find_clr(ft_atoi(tmp[0]), ft_atoi(tmp[1]), ft_atoi(tmp[2]));
		scene->is_duplicate[5]++;
	}
	else
	{
		if (ft_atoi(tmp[0]) == -1 || ft_atoi(tmp[1]) == -1
			|| ft_atoi(tmp[2]) == -1)
			return (ft_putendl_fd(ERR, 2), ft_putendl_fd(C_INV, 2),
				free_split(tmp), false);
		scene->cc = find_clr(ft_atoi(tmp[0]), ft_atoi(tmp[1]), ft_atoi(tmp[2]));
		scene->is_duplicate[4]++;
	}
	scene->counter++;
	return (true);
}

bool	get_colors(t_scene_infn *scene, char **str, char *val)
{
	char	**tmp;
	char	*tmp2;

	if (!ft_strncmp(str[0], "C", ft_strlen(str[0]))
		|| !ft_strncmp(str[0], "F", ft_strlen(str[0])))
	{
		if (str[1])
		{
			tmp2 = ft_strtrim(val + 1, " \t");
			tmp = ft_ssplit(tmp2, ",\n");
			if (tmp2)
				free(tmp2);
			if (tmp)
			{
				if (!get_ind_clrs(str, tmp, scene))
					return (false);
				free_split(tmp);
			}
			else
				return (ft_putendl_fd(ERR, 2), false);
		}
		else
			return (ft_putendl_fd(ERR, 2), ft_putendl_fd(C_ABS, 2), false);
	}
	return (true);
}
