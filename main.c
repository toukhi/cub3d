/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abiru <abiru@student.42abudhabi.ae>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 21:19:50 by abiru             #+#    #+#             */
/*   Updated: 2023/05/29 20:49:07 by abiru            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "cub3D.h"
#include <fcntl.h>
#include <stdbool.h>

void free_split(char **str)
{
	size_t	i;

	i = 0;
	if (!str)
		return ;
	while (str + i && str[i])
	{
		free(str[i]);
		str[i] = 0;
		i++;
	}
	free(str);
	str = 0;
	return ;
}

static size_t get_split_size(char **str)
{
	size_t	i;

	i = 0;
	while (str + i && str[i])
		i++;
	return (i);
}

static bool	is_space(char *str)
{
	size_t i;

	i = 0;
	while (str + i && str[i])
	{
		if (str[i] != ' ' && str[i] != '\t')
			return (false);
		else
			i++;
	}
	return (true);
}

static bool	check_empty_field(char **str)
{
	size_t	i;

	i = 0;
	while (str + i && str[i])
	{
		if (is_space(str[i]))
			return (true);
		i++;
	}
	return (false);
}

static bool	check_duplicate(t_scene_infn *scene, unsigned short index)
{
	if (scene->is_duplicate[index] == 1)
		return (true);
	return (false);
}

bool	validate_texture(t_scene_infn *scene, char **str)
{
	if (str[0] && !ft_strncmp(str[0], "NO", ft_strlen(str[0])))
	{
		if (check_duplicate(scene, 0))
			return (ft_putendl_fd("error", 2), ft_putendl_fd(N_DUP, 2), false);
		else if (get_split_size(str) > 2)
			return (ft_putendl_fd("error", 2), ft_putendl_fd(N_EXT, 2), false);
		else if (str + 1 && str[1])
		{
			scene->textures[0] = ft_strdup(str[1]);
			scene->is_duplicate[0]++;
		}
		else
			return (ft_putendl_fd("error", 2), ft_putendl_fd(N_ERR, 2), false);
	}
	else if (str[0] && !ft_strncmp(str[0], "SO", ft_strlen(str[0])))
	{
		if (check_duplicate(scene, 1))
			return (ft_putendl_fd("error", 2), ft_putendl_fd(S_DUP, 2), false);
		else if (get_split_size(str) > 2)
			return (ft_putendl_fd("error", 2), ft_putendl_fd(S_EXT, 2), false);
		else if (str + 1 && str[1])
		{
			scene->textures[1] = ft_strdup(str[1]);
			scene->is_duplicate[1]++;
		}
		else
			return (ft_putendl_fd("error", 2), ft_putendl_fd(S_ERR, 2), false);
	}
	else if (str[0] && !ft_strncmp(str[0], "WE", ft_strlen(str[0])))
	{
		if (check_duplicate(scene, 2))
			return (ft_putendl_fd("error", 2), ft_putendl_fd(W_DUP, 2), false);
		else if (get_split_size(str) > 2)
			return (ft_putendl_fd("error", 2), ft_putendl_fd(W_EXT, 2), false);
		else if (str + 1 && str[1])
		{
			scene->textures[2] = ft_strdup(str[1]);
			scene->is_duplicate[2]++;
		}
		else
			return (ft_putendl_fd("error", 2), ft_putendl_fd(W_ERR, 2), false);
	}
	else if (str[0] && !ft_strncmp(str[0], "EA", ft_strlen(str[0])))
	{
		if (check_duplicate(scene, 3))
			return (ft_putendl_fd("error", 2), ft_putendl_fd(E_DUP, 2), false);
		else if (get_split_size(str) > 2)
			return (ft_putendl_fd("error", 2), ft_putendl_fd(E_EXT, 2), false);
		if (str + 1 && str[1])
		{
			scene->textures[3] = ft_strdup(str[1]);
			scene->is_duplicate[3]++;
		}
		else
			return (ft_putendl_fd("error", 2), ft_putendl_fd(E_ERR, 2), false);
	}
	return (true);
}

bool	get_colors(t_scene_infn *scene, char **str)
{
	char **tmp;

	if (!ft_strncmp(str[0], "C", ft_strlen(str[0])) || !ft_strncmp(str[0], "F", ft_strlen(str[0])))
	{
		if (str[1])
		{
			tmp = ft_ssplit(str[1], ",");
			if (tmp)
			{
				if (get_split_size(tmp) < 3 || check_empty_field(tmp))
				{
					ft_putendl_fd("error", 2);
					ft_putendl_fd("Invalid color", 2);
					free_split(tmp);
					return (false);
				}
				if (!ft_strncmp(str[0], "C", ft_strlen(str[0])))
				{
					scene->ceil_clr[0] = ft_atoi(tmp[0]);
					scene->ceil_clr[1] = ft_atoi(tmp[1]);
					scene->ceil_clr[2] = ft_atoi(tmp[2]);
					scene->is_duplicate[4]++;
				}
				else
				{
					scene->floor_clr[0] = ft_atoi(tmp[0]);
					scene->floor_clr[1] = ft_atoi(tmp[1]);
					scene->floor_clr[2] = ft_atoi(tmp[2]);
					scene->is_duplicate[5]++;
				}
				free_split(tmp);
			}
			else
				return (ft_putendl_fd("error", 2), false);
		}
	}
	return (true);
}

bool	validate_map(int fd, t_scene_infn *scene)
{
	char *str;
	char **str2;

	str = get_next_line(fd);
	str2 = 0;
	while (str)
	{
		// printf("heere: %s\n", str);
		str2 = ft_ssplit(str, "\t\n ");
		if (str2 && get_split_size(str2))
		{
			if (!validate_texture(scene, str2) || !get_colors(scene, str2))
			{
				free(str);
				free_split(str2);
				return (false);
			}
		}
		free_split(str2);
		free(str);
		str = get_next_line(fd);
	}
		// for (int i=0; i<4; i++)
		// 	printf("%s\n", scene->textures[i]);
		// for (int i=0; i<3; i++)
		// 	printf("%d, ", scene->ceil_clr[i]);
		// for (int i=0; i<3; i++)
		// 	printf("%d, ", scene->floor_clr[i]);
	return (true);
}

int	main(int ac, char **av)
{
	t_scene_infn scene;
	for (int i=0; i<6; i++)
		scene.is_duplicate[i] = 0;
	if (ac != 2)
	{
		ft_putstr_fd("Usage: ./cub3D map_file\n", 2);
		exit(EXIT_FAILURE);
	}

	int map_fd = open(av[1], O_RDONLY);
	if (map_fd == -1)
	{
		perror("open");
		exit(EXIT_FAILURE);
	}
	if (!validate_map(map_fd, &scene))
	{
		close(map_fd);
		return (EXIT_FAILURE);
	}
	close(map_fd);
	for (size_t i=0; i<4; i++)
		if (scene.textures[i])
			free(scene.textures[i]);
	return (EXIT_SUCCESS);
}
