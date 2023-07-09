/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils3.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abiru <abiru@student.42abudhabi.ae>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/09 11:25:48 by abiru             #+#    #+#             */
/*   Updated: 2023/07/09 11:39:47 by abiru            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

size_t	get_real_size(t_scene_infn *scene)
{
	int		i;
	int		j;
	bool	flag;

	i = -1;
	while (++i < (int)scene->size)
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
	}
	return (i);
}

bool	check_texture(char *str, char *msg)
{
	int	fd;

	fd = open(str, O_RDWR);
	if (errno == EISDIR)
		return (ft_putendl_fd(ERR, 2), ft_putstr_fd(msg, 2),
			ft_putendl_fd("Texture is a directory", 2), true);
	if (fd != -1)
		close(fd);
	fd = open(str, O_RDONLY);
	if (fd == -1)
		return (ft_putendl_fd(ERR, 2), ft_putstr_fd(msg, 2),
			perror(""), true);
	close(fd);
	return (false);
}

void	update_values(t_vars *vars, short index, char **str)
{
	vars->scene.textures[index] = ft_strdup(str[1]);
	vars->scene.counter++;
	vars->scene.is_duplicate[index]++;
}
