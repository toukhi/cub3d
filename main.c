/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abiru <abiru@student.42abudhabi.ae>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 21:19:50 by abiru             #+#    #+#             */
/*   Updated: 2023/05/31 17:36:15 by abiru            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	main(int ac, char **av)
{
	t_scene_infn	scene;
	int				map_fd;

	if (ac != 2)
	{
		ft_putendl_fd("Usage: ./cub3D map_file", 2);
		exit(EXIT_FAILURE);
	}
	map_fd = open(av[1], O_RDONLY);
	if (map_fd == -1)
	{
		perror("open");
		exit(EXIT_FAILURE);
	}
	init_struct(&scene);
	if (!get_map_size(&scene, &map_fd, av[1]))
	{
		ft_putendl_fd("error", 2);
		ft_putendl_fd("Invalid map", 2);
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
