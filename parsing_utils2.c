/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abiru <abiru@student.42abudhabi.ae>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 10:54:09 by abiru             #+#    #+#             */
/*   Updated: 2023/06/07 16:37:11 by abiru            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

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
		j = scene->size;
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

bool	check_texture(char *str)
{
	int	fd;

	fd = open(str, O_RDWR);
	if (errno == EISDIR)
		return (ft_putendl_fd(ERR, 2),
			ft_putendl_fd("Texture is a directory", 2), true);
	if (fd != -1)
		close(fd);
	fd = open(str, O_RDONLY);
	if (fd == -1)
		return (ft_putendl_fd(ERR, 2), perror("Open"), true);
	close(fd);
	return (false);
}

/*
	- looks for bad characters and multiple starting position
*/
bool	search_bad_chars(char **arr, t_scene_infn *scene)
{
	size_t	i;
	size_t	j;

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
					scene->s_orient = arr[i][j];
		}
	}
	if (scene->s_orient == '0')
		return (ft_putendl_fd(ERR, 2), ft_putendl_fd(M_ORIENT, 2), true);
	return (false);
}
