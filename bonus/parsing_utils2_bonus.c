/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils2_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-touk <yel-touk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 10:54:09 by abiru             #+#    #+#             */
/*   Updated: 2023/07/18 18:56:50 by yel-touk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D_bonus.h"

bool	check_empty_field(char **str)
{
	size_t	i;

	i = 0;
	if (!str)
		return (false);
	while (str[i])
	{
		if (is_space(str[i]))
			return (true);
		i++;
	}
	return (false);
}

void	free_map(t_scene_infn *scene, int i)
{
	size_t	j;
	size_t	k;

	if (i == -1)
		j = scene->tmp_size;
	else
		j = (size_t)i;
	k = 0;
	while (k < j)
	{
		free(scene->content[k]);
		scene->content[k] = 0;
		k++;
	}
	free(scene->content);
	scene->content = 0;
}

size_t	find_row_size(char *arr)
{
	size_t	i;

	i = 0;
	if (!arr)
		return (i);
	while (arr[i])
		i++;
	return (i);
}

void	set_start_pos(t_scene_infn *scene, int x, int y, char orientation)
{
	scene->s_orient = orientation;
	scene->s_pos_x = x;
	scene->s_pos_y = y;
}

/*
	- looks for bad characters and multiple starting position
*/
bool	search_bad_chars(char **arr, t_scene_infn *scene)
{
	int	i;
	int	j;

	i = -1;
	while (arr[++i])
	{
		j = -1;
		while (arr[i][++j])
		{
			if (scene->s_orient != '0' && (arr[i][j] == 'N' || arr[i][j] == 'S'
				|| arr[i][j] == 'E' || arr[i][j] == 'W'))
				return (ft_putendl_fd(ERR, 2), ft_putendl_fd(DUP_CHAR, 2), 1);
			if (arr[i][j] != '1' && arr[i][j] != '0' && arr[i][j] != ' '
				&& arr[i][j] != '\t' && arr[i][j] != 'N' && arr[i][j] != 'S'
				&& arr[i][j] != 'E' && arr[i][j] != 'W')
				return (ft_putendl_fd(ERR, 2), ft_putendl_fd(BAD_CHAR, 2), 1);
			if (arr[i][j] == 'N' || arr[i][j] == 'S'
				|| arr[i][j] == 'E' || arr[i][j] == 'W')
				set_start_pos(scene, j, i, arr[i][j]);
		}
	}
	if (scene->s_orient == '0')
		return (ft_putendl_fd(ERR, 2), ft_putendl_fd(M_ORIENT, 2), true);
	return (false);
}
