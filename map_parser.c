/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abiru <abiru@student.42abudhabi.ae>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/02 23:24:04 by abiru             #+#    #+#             */
/*   Updated: 2023/06/20 17:38:15 by abiru            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

char	**construct_map(char *str, t_scene_infn *scene)
{
	size_t	i;
	char	*str2;
	char	**arr;

	arr = (char **)malloc(sizeof(char *) * (scene->size + 1));
	if (!arr)
		return (free(str), ft_putendl_fd(ERR, 2), perror("Malloc"), NULL);
	i = 0;
	while (str)
	{
		str2 = ft_strtrim(str, "\n");
		free(str);
		arr[i++] = str2;
		str = get_next_line(scene->map_fd);
	}
	arr[i] = 0;
	if (str)
		free(str);
	return (arr);
}

static bool	check_spaces(t_scene_infn *scene, int i, int j)
{
	// if (ft_isspace(scene->content[i][j]) && (i == 0 ||
	// i == (int)(scene->size - 1) || (i != 0 && i !=
	// (int)(scene->size - 1) && ((int)find_row_size(scene->content[i - 1]) <= j
	// || (int)find_row_size(scene->content[i + 1]) <= j))))
	// 	return (ft_putendl_fd(ERR, 2), ft_putendl_fd(M_OPEN, 2), true);
	if (ft_isspace(scene->content[i][j]))
	{
		if (i > 0 && (int)find_row_size(scene->content[i - 1]) >= j
			&& scene->content[i - 1][j] && !(scene->content[i - 1][j] == '1'
			|| ft_isspace(scene->content[i - 1][j])))
			return (ft_putendl_fd(ERR, 2), ft_putendl_fd(M_OPEN, 2), true);
		else if (i < (int)scene->size - 1
			&& (int)find_row_size(scene->content[i + 1]) >= j
			&& scene->content[i + 1][j] && !(scene->content[i + 1][j] == '1'
			|| ft_isspace(scene->content[i + 1][j])))
			return (ft_putendl_fd(ERR, 2), ft_putendl_fd(M_OPEN, 2), true);
		else if (j > 0 && !(scene->content[i][j - 1] == '1'
			|| ft_isspace(scene->content[i][j - 1])))
			return (ft_putendl_fd(ERR, 2), ft_putendl_fd(M_OPEN, 2), true);
		else if (j < (int)find_row_size(scene->content[i]) - 1
			&& !(scene->content[i][j + 1] == '1'
			|| ft_isspace(scene->content[i][j + 1])))
			return (ft_putendl_fd(ERR, 2), ft_putendl_fd(M_OPEN, 2), true);
	}
	return (false);
}

/*
	- Map is invalid if:
	-> it contains an empty line
	-> if the 1st column's value in a row isn't 1, ' ', or '\t'
	-> if there is at least 1 item with a value different from 
	1, ' ', & '\t' on the 1st & last row
	-> if a space char is found on any column, and it is not 
		surrounded by 1 or ' ' or '\t'
*/
static bool	check_open_wall(t_scene_infn *scene, char **arr)
{
	int		i;
	int		j;

	i = -1;
	while (++i < (int)scene->size)
	{
		j = -1;
		if (!ft_strlen(arr[i]))
			return (ft_putendl_fd(ERR, 2), ft_putendl_fd(ERR_L_EMP, 2), true);
		while (arr[i][++j])
		{
			if (check_borders(scene, scene->content, i, j))
				return (true);
			if (check_spaces(scene, i, j))
				return (true);
		}
	}
	return (false);
}

static void	replace_spaces(t_scene_infn *scene)
{
	size_t	i;
	size_t	j;

	i = 0;
	while (scene->content[i])
	{
		j = 0;
		while (scene->content[i][j])
		{
			if (ft_isspace(scene->content[i][j]))
				scene->content[i][j] = '1';
			j++;
		}
		i++;
	}
}

/*
	// populate map array
	// check for illegal chars (char except 1, 0, N, S, E, W, ' ', '\t', '\n')
	// check for multiple starting values (duplicate starting values)
	// check for open wall
*/

size_t	get_real_size(t_scene_infn *scene)
{
	size_t	i;
	size_t	j;
	bool	flag;

	i = 0;
	while (i < scene->size)
	{
		flag = true;
		if (!ft_strlen(scene->content[i]))
		{
			j = i;
			while (scene->content[j])
			{
				if (ft_strlen(scene->content[j]))
				{
					flag = false;
					break ;
				}
				j++;
			}
			if (flag)
				return (i);
		}
		i++;
	}
	return (i);
}

bool	validate_map_content(char *str, t_scene_infn *scene)
{
	scene->content = construct_map(str, scene);
	if (!scene->content)
		return (false);
	scene->tmp_size = scene->size;
	scene->size = get_real_size(scene);
	if (search_bad_chars(scene->content, scene))
		return (free_map(scene, -1), false);
	if (check_open_wall(scene, scene->content))
		return (free_map(scene, -1), false);
	replace_spaces(scene);
	set_longest_line(scene);
	if (!create_minimap(scene))
		return (free_map(scene, -1), false);
	scene->counter++;
	return (true);
}
