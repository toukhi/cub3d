/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abiru <abiru@student.42abudhabi.ae>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 17:35:54 by abiru             #+#    #+#             */
/*   Updated: 2023/07/17 14:37:54 by abiru            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

bool	check_borders(t_scene_infn *scene, char **arr, int i, int j)
{
	if (((j == 0 || !arr[i][j + 1]) && (arr[i][j] != '1'
		&& !ft_isspace(arr[i][j])))
		|| ((i == 0 || i == (int)scene->size - 1)
		&& (arr[i][j] != '1' && !ft_isspace(arr[i][j])))
		|| (arr[i][j] != '1' && !ft_isspace(arr[i][j])
		&& ((int)find_row_size(arr[i + 1]) <= j
		|| (int)find_row_size(arr[i - 1]) <= j)))
		return (ft_putendl_fd(ERR, 2), ft_putendl_fd(M_OPEN, 2), true);
	return (false);
}

bool	map_detected(char **str)
{
	if (!ft_strncmp(str[0], "C", ft_strlen(str[0]))
		|| !ft_strncmp(str[0], "F", ft_strlen(str[0]))
		|| !ft_strcmp(str[0], "EA")
		|| !ft_strcmp(str[0], "WE")
		|| !ft_strcmp(str[0], "NO")
		|| !ft_strcmp(str[0], "SO"))
		return (false);
	return (true);
}

/*
	* reads a line, trims space character including newline, 
	* splits the string using tabs and spaces to validate texture information,
	* uses the trimmed string and splits it using comma to validate color infn
*/
bool	validate_map(t_vars *vars)
{
	char	*str;
	char	**str2;
	char	*str3;

	str = get_next_line(vars->scene.map_fd);
	while (str)
	{
		str3 = ft_strtrim(str, " \t\r\v\f\n");
		str2 = ft_ssplit(str3, " \t\r\v\f\n");
		if (str2 && get_split_size(str2))
		{
			if (!validate_texture(vars, str2)
				|| !get_colors(&vars->scene, str2, str3))
				return (free_split(str2), free(str), free(str3), false);
			if (map_detected(str2))
			{
				if (!validate_map_content(str, &vars->scene))
					return (free_split(str2), free(str3), false);
				return (free_split(str2), free(str3), true);
			}
		}
		free_mem_parsing(str, str2, str3);
		str = get_next_line(vars->scene.map_fd);
	}
	return (true);
}

bool	get_map_size(t_scene_infn *scene, char *map)
{
	char	**tmp;
	char	*line;
	bool	flag;

	flag = false;
	tmp = 0;
	line = get_next_line(scene->map_fd);
	while (line)
	{
		tmp = ft_ssplit(line, " \t\r\v\f\n");
		if (!flag && tmp && map_detected(tmp))
			flag = true;
		if (flag)
			scene->size++;
		free(line);
		free_split(tmp);
		line = get_next_line(scene->map_fd);
	}
	free(line);
	close(scene->map_fd);
	scene->map_fd = open(map, O_RDONLY);
	return (true);
}
