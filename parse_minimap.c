/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_minimap.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abiru <abiru@student.42abudhabi.ae>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/16 15:24:21 by abiru             #+#    #+#             */
/*   Updated: 2023/06/16 15:42:17 by abiru            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static void	copy_content(t_scene_infn *scene, size_t i)
{
	size_t	j;

	j = 0;
	while (scene->content[i] && j < scene->longest)
	{
		if (j < ft_strlen(scene->content[i]))
			scene->minimap[i][j] = scene->content[i][j];
		else
			scene->minimap[i][j] = '1';
		j++;
	}
	scene->minimap[i][j] = 0;
}

bool	create_minimap(t_scene_infn *scene)
{
	size_t	i;

	scene->minimap = (char **)malloc(sizeof(char *) * (scene->size + 1));
	if (!scene->minimap)
		return (ft_putendl_fd(ERR, 2), perror("Malloc"), false);
	i = 0;
	while (i < scene->size)
	{
		scene->minimap[i] = (char *)malloc(sizeof(char) * (scene->longest + 1));
		if (!scene->minimap[i])
			return (free_split(scene->minimap), ft_putendl_fd(ERR, 2), perror("Malloc"), false);
		copy_content(scene, i);
		i++;
	}
	scene->minimap[i] = 0;
	return (true);
}