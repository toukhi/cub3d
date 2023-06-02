/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abiru <abiru@student.42abudhabi.ae>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/02 23:24:04 by abiru             #+#    #+#             */
/*   Updated: 2023/06/03 00:11:49 by abiru            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

bool	populate_row(char *str, t_scene_infn *scene, size_t index)
{
	size_t	i;
	size_t	j;

	i = 0;
	scene->content[index] = (int *)malloc(sizeof(int) * (ft_strlen(str) + 1));
	if (!scene->content[index])
		return (ft_putendl_fd(ERR, 2), perror("Malloc"), false);
	j = ft_strlen(str);
	while (i < j)
	{
		scene->content[index][i] = (int)str[i];
		i++;
	}
	scene->content[index][i] = 0;
	return (true);
}

/*
	- populates rows and columns of the 2-d array
*/
bool	populate_map_arr(char *str, t_scene_infn *scene)
{
	size_t	i;
	char	*str2;

	scene->content = (int **)malloc(sizeof(int *) * (scene->size + 1));
	if (!scene->content)
		return (ft_putendl_fd(ERR, 2), perror("Malloc"), false);
	i = 0;
	while (str)
	{
		str2 = ft_strtrim(str, "\n");
		free(str);
		if (!populate_row(str2, scene, i))
			return (free(str2), free_map(scene, i), false);
		i++;
		free(str2);
		str = get_next_line(scene->map_fd);
	}
	scene->content[i] = 0;
	if (str)
		free(str);
	// i = 0;
	// size_t j;
	// while (scene->content[i])
	// {
	// 	j = 0;
	// 	while (scene->content[i][j])
	// 	{
	// 		printf("%d ", scene->content[i][j]);
	// 		j++;
	// 	}
	// 	printf("\n");
	// 	i++;
	// }
	return (true);
}

/*
	- looks for bad characters and multiple starting position
*/
bool search_bad_chars(t_scene_infn *scene)
{
	size_t	i;
	size_t	j;
	bool	fnd_pos;

	i = -1;
	fnd_pos = false;
	while (scene->content[++i])
	{
		j = -1;
		while (scene->content[i][++j])
		{
			if (fnd_pos && (scene->content[i][j] == 'N' || scene->content[i][j] == 'S'
				|| scene->content[i][j] == 'E' || scene->content[i][j] == 'W'))
					return (ft_putendl_fd(ERR, 2), ft_putendl_fd(DUP_CHAR, 2), true);
			if (scene->content[i][j] != '1' && scene->content[i][j] != '0' && scene->content[i][j] != ' '
				&& scene->content[i][j] != '\t' && scene->content[i][j] != 'N' && scene->content[i][j] != 'S'
				&& scene->content[i][j] != 'E' && scene->content[i][j] != 'W')
					return (ft_putendl_fd(ERR, 2), ft_putendl_fd(BAD_CHAR, 2), true);
			if (scene->content[i][j] == 'N' || scene->content[i][j] == 'S'
				|| scene->content[i][j] == 'E' || scene->content[i][j] == 'W')
			{
					scene->s_orient = scene->content[i][j];
					fnd_pos = true;
			}
		}
	}
	if (!fnd_pos)
		return (ft_putendl_fd(ERR, 2), ft_putendl_fd(M_ORIENT, 2), true);
	return (false);
}

bool validate_map_content(char *str, t_scene_infn *scene)
{
	// populate map array
	// check for illegal chars (char except 1, 0, N, S, E, W, ' ', '\t', '\n')
	// check for multiple starting values (duplicate starting values)
	// check for open wall
	if (!populate_map_arr(str, scene))
		return (false);
	if (search_bad_chars(scene))
		return (free_map(scene, -1), false);
	(void)str;
	(void)scene;
	return (true);
}