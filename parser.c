/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abiru <abiru@student.42abudhabi.ae>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 17:35:54 by abiru             #+#    #+#             */
/*   Updated: 2023/06/02 17:22:03 by abiru            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

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

bool validate_map_content(char *str, t_scene_infn *scene)
{
	(void)str;
	(void)scene;
	return (true);
}

bool	validate_map(t_scene_infn *scene)
{
	char *str;
	char **str2;
	char *str3;

	str = get_next_line(scene->map_fd);
	str2 = 0;
	while (str)
	{
		str3 = ft_strtrim(str, " \t\n");
		free(str);
		str2 = ft_ssplit(str3, "\t ");
		if (str2 && get_split_size(str2))
		{
			if (!validate_texture(scene, str2) || !get_colors(scene, str2, str3))
				return (free_split(str2), free(str3), false);
			else if (map_detected(str2))
			{
				if (!validate_map_content(str, scene))
					return (free_split(str2), free(str3), ft_putendl_fd(ERR, 2), ft_putendl_fd("Invalid map", 2), false);
				return (free_split(str2), free(str3), true);
			}
		}
		free(str3);
		free_split(str2);
		str = get_next_line(scene->map_fd);
	}
	// should be uncommented after validating map content

	// if (scene->counter < 7)
	// {
	// 	ft_putendl_fd(ERR, 2);
	// 	ft_putendl_fd("Incomplete map", 2);
	// 	return (false);
	// }
	for (int i=0; i<4; i++)
		printf("%s\n", scene->textures[i]);
	for (int i=0; i<3; i++)
		printf("%d, ", scene->ceil_clr[i]);
	for (int i=0; i<3; i++)
		printf("%d, ", scene->floor_clr[i]);
	return (true);
}

bool	get_map_size(t_scene_infn *scene, char *map)
{
	char	**tmp;
	char	*line;
	size_t	counter;
	bool	flag;

	counter = 0;
	flag = false;
	tmp = 0;
	line = get_next_line(scene->map_fd);
	while (line)
	{
		tmp = ft_ssplit(line, " \t\n");
		if (!flag && tmp && map_detected(tmp))
			flag = true;
			// && (get_split_size(tmp) >= 1 && ft_strcmp(tmp[0], ""))
		if (flag)
			counter++;
		free(line);
		free_split(tmp);
		line = get_next_line(scene->map_fd);
	}
	scene->size = counter;
	free(line);
	close(scene->map_fd);
	scene->map_fd = open(map, O_RDONLY);
	return (true);
}
