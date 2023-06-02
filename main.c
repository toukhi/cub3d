/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abiru <abiru@student.42abudhabi.ae>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 21:19:50 by abiru             #+#    #+#             */
/*   Updated: 2023/06/02 23:43:13 by abiru            ###   ########.fr       */
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

int	main(int ac, char **av)
{
	t_scene_infn	scene;

	if (!do_init_validation(ac, av, &scene))
		return (EXIT_FAILURE);
	init_struct(&scene);
	if (!get_map_size(&scene, av[1]))
		return (ft_putendl_fd(ERR, 2), ft_putendl_fd("Invalid map", 2), EXIT_FAILURE);
	// printf("size: %zu\n", scene.size);
	if (!validate_map(&scene))
	{
		close(scene.map_fd);
		return (EXIT_FAILURE);
	}
	close(scene.map_fd);
	for (size_t i=0; i<4; i++)
		if (scene.textures[i])
			free(scene.textures[i]);
	return (EXIT_SUCCESS);
}
