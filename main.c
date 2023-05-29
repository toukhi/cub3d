/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abiru <abiru@student.42abudhabi.ae>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 21:19:50 by abiru             #+#    #+#             */
/*   Updated: 2023/05/29 13:00:49 by abiru            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "cub3D.h"
#include <fcntl.h>

void validate_map(int fd)
{
	char *str;

	str = get_next_line(fd);
	while (str)
	{
		if (str && ft_strlen(str))
		{
			if (!ft_strncmp(str, "NO", 2))
			{
				char **str2 = ft_ssplit(str, ",	 ");
				while (str2 && *str2)
				{
					printf("%s\n", *str2);
					str2++;
				}
			}
		}
		printf("%s", str);
		free(str);
		str = get_next_line(fd);
	}
}

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
	validate_map(map_fd);
	close(map_fd);
}