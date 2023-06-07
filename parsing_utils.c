/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abiru <abiru@student.42abudhabi.ae>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 17:38:13 by abiru             #+#    #+#             */
/*   Updated: 2023/06/07 16:36:19 by abiru            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	init_struct(t_scene_infn *scene)
{
	int	i;

	i = -1;
	scene->counter = 0;
	scene->size = 0;
	scene->s_orient = '0';
	scene->content = 0;
	while (++i < 7)
		scene->is_duplicate[i] = 0;
	i = -1;
	while (++i < 4)
		scene->textures[i] = NULL;
}

void	free_split(char **str)
{
	size_t	i;

	i = 0;
	if (!str)
		return ;
	while (str[i])
	{
		free(str[i]);
		str[i] = 0;
		i++;
	}
	free(str);
	str = 0;
	return ;
}

size_t	get_split_size(char **str)
{
	size_t	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
		i++;
	return (i);
}

bool	is_space(char *str)
{
	size_t	i;

	i = 0;
	if (!str)
		return (false);
	while (str[i])
	{
		if (str[i] != ' ' && str[i] != '\t')
			return (false);
		i++;
	}
	return (true);
}

bool	check_duplicate(t_scene_infn *scene, unsigned short index)
{
	if (scene->is_duplicate[index] == 1)
		return (true);
	return (false);
}
