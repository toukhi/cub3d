/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abiru <abiru@student.42abudhabi.ae>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 21:19:50 by abiru             #+#    #+#             */
/*   Updated: 2023/06/04 20:42:42 by abiru            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

/*
	- checks the number of arguments given to the program
	- checks if the argument ends with .cub
	- checks if the argument is a directory
*/
static bool	do_init_validation(int ac, char **av, t_scene_infn *scene)
{
	if (ac != 2)
		return (ft_putendl_fd(ERR, 2), ft_putendl_fd(USG_ERR, 2), false);
	if (ft_strlen(av[1]) < 4 || ft_strcmp(av[1] + ft_strlen(av[1]) - 4, ".cub"))
		return (ft_putendl_fd(ERR, 2), ft_putendl_fd(ERR_EXTENSION, 2), false);
	scene->map_fd = open(av[1], O_RDWR);
	if (errno == EISDIR)
		return (ft_putendl_fd(ERR, 2), perror("Open"), false);
	close(scene->map_fd);
	scene->map_fd = open(av[1], O_RDONLY);
	if (scene->map_fd == -1)
		return (ft_putendl_fd(ERR, 2), perror("Open"), false);
	return (true);
}

static void	cleanup(t_scene_infn *scene)
{
	int	i;

	free_split(scene->content);
	i = 0;
	while (i < 4)
	{
		if (scene->textures[i])
			free(scene->textures[i]);
		scene->textures[i] = 0;
		i++;
	}
}

bool	check_textures(t_scene_infn *scene)
{
	unsigned short	i;

	i = 0;
	while (i < 4)
	{
		if (check_texture(scene->textures[i]))
			return (false);
		i++;
	}
	return (true);
}

int	main(int ac, char **av)
{
	t_scene_infn	scene;

	if (!do_init_validation(ac, av, &scene))
		return (1);
	init_struct(&scene);
	if (!get_map_size(&scene, av[1]))
		return (ft_putendl_fd(ERR, 2), ft_putendl_fd("Invalid map", 2), 1);
	if (!validate_map(&scene))
	{
		close(scene.map_fd);
		return (1);
	}
	close(scene.map_fd);
	if (scene.counter != 7)
		return (cleanup(&scene), ft_putendl_fd(ERR, 2),
			ft_putendl_fd(S_INC, 2), 1);
	if (!check_textures(&scene))
		return (cleanup(&scene), 1);
	cleanup(&scene);
	return (0);
}
