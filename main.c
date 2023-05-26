/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abiru <abiru@student.42abudhabi.ae>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 21:19:50 by abiru             #+#    #+#             */
/*   Updated: 2023/05/26 21:22:27 by abiru            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "cub3D.h"
#include <fcntl.h>

int	main(int ac, char **av)
{
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
	printf("%s", get_next_line(map_fd));
	close(map_fd);
}