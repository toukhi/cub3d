/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   c_parser.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abiru <abiru@student.42abudhabi.ae>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 17:53:15 by abiru             #+#    #+#             */
/*   Updated: 2023/05/31 17:53:43 by abiru            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

bool	get_colors(t_scene_infn *scene, char **str, char *val)
{
	char	**tmp;
	char	*tmp2;

	if (!ft_strncmp(str[0], "C", ft_strlen(str[0])) || !ft_strncmp(str[0], "F", ft_strlen(str[0])))
	{
		if (str[1])
		{
			tmp2 = ft_strtrim(val + 1, " \t");
			tmp = ft_ssplit(tmp2, ",\n");
			if (tmp2)
				free(tmp2);
			// printf("size: %zu\t%s\t%s\t%s\n", get_split_size(tmp), tmp[0], tmp[1], tmp[2]);
			if (tmp)
			{
				if (get_split_size(tmp) != 3 || check_empty_field(tmp))
					return (ft_putendl_fd(ERR, 2), ft_putendl_fd(EXT_ERR, 2), free_split(tmp), false);
				if (!ft_strncmp(str[0], "C", ft_strlen(str[0])))
				{
					scene->ceil_clr[0] = ft_atoi(tmp[0]);
					scene->ceil_clr[1] = ft_atoi(tmp[1]);
					scene->ceil_clr[2] = ft_atoi(tmp[2]);
					if (scene->ceil_clr[0] == -1 || scene->ceil_clr[1] == -1 || scene->ceil_clr[2] == -1)
						return (ft_putendl_fd(ERR, 2), ft_putendl_fd(C_INV, 2), free_split(tmp), false);
					scene->counter++;
					scene->is_duplicate[4]++;
				}
				else
				{
					scene->floor_clr[0] = ft_atoi(tmp[0]);
					scene->floor_clr[1] = ft_atoi(tmp[1]);
					scene->floor_clr[2] = ft_atoi(tmp[2]);
					if (scene->floor_clr[0] == -1 || scene->floor_clr[1] == -1 || scene->floor_clr[2] == -1)
						return (ft_putendl_fd(ERR, 2), ft_putendl_fd(F_INV, 2), free_split(tmp), false);
					scene->counter++;
					scene->is_duplicate[5]++;
				}
				free_split(tmp);
			}
			else
				return (ft_putendl_fd(ERR, 2), ft_putendl_fd("Splitting error", 2), false);
		}
		else
			return (ft_putendl_fd(ERR, 2), ft_putendl_fd(C_ABS, 2), false);
	}
	return (true);
}