/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youssef <youssef@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 17:35:54 by abiru             #+#    #+#             */
/*   Updated: 2023/06/17 14:39:58 by youssef          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

bool	check_borders(t_scene_infn *scene, char **arr, int i, int j)
{
	if (((j == 0 || !arr[i][j + 1]) && (arr[i][j] != '1' && arr[i][j] != ' '
		&& arr[i][j] != '\t')) || ((i == 0 || i == (int)scene->size - 1)
		&& (arr[i][j] != '1' && arr[i][j] != ' ' && arr[i][j] != '\t'))
		|| (arr[i][j] == '0' && (i == (int)scene->size - 1 ||
		(int)find_row_size(arr[i + 1]) <= j
			|| (int)find_row_size(arr[i - 1]) <= j)))
		return (ft_putendl_fd(ERR, 2), ft_putendl_fd(M_OPEN, 2), true);
	return (false);
}

bool	map_detected(char **str)
{
	if (!ft_strncmp(str[0], "C", ft_strlen(str[0]))
		|| !ft_strncmp(str[0], "F", ft_strlen(str[0]))
		|| !ft_strncmp(str[0], "EA", ft_strlen(str[0]))
		|| !ft_strncmp(str[0], "WE", ft_strlen(str[0]))
		|| !ft_strncmp(str[0], "NO", ft_strlen(str[0]))
		|| !ft_strncmp(str[0], "SO", ft_strlen(str[0])))
		return (false);
	return (true);
}

// static bool	validate_elts(t_scene_infn *scene, char *str, char **str2,
// 	char *str3)
// {
// 	if (!validate_texture(scene, str2) || !get_colors(scene, str2, str3))
// 		return (free_split(str2), free(str), free(str3), false);
// 	else if (map_detected(str2))
// 	{
// 		free_split(str2);
// 		free(str3);
// 		if (!validate_map_content(str, scene))
// 			return (false);
// 		return (true);
// 	}
// 	return (true);
// }

/*
	- reads a line, trims space character including newline, 
	then splits the string using tabs and spaces to validate texture information,
	uses the trimmed string and splits it using comma to validate color information
*/
bool	validate_map(t_scene_infn *scene)
{
	char	*str;
	char	**str2;
	char	*str3;

	str = get_next_line(scene->map_fd);
	str2 = 0;
	while (str)
	{
		str3 = ft_strtrim(str, " \t\n");
		str2 = ft_ssplit(str3, "\t ");
		if (str2 && get_split_size(str2))
		{
			if (!validate_texture(scene, str2) || !get_colors(scene, str2, str3))
				return (free_split(str2), free(str), free(str3), false);
			if (map_detected(str2))
			{
				if (!validate_map_content(str, scene))
					return (free_split(str2), free(str3), false);
				return (free_split(str2), free(str3), true);
			}
		}
		free(str);
		free(str3);
		free_split(str2);
		str = get_next_line(scene->map_fd);
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
		tmp = ft_ssplit(line, " \t\n");
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
