/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youssef <youssef@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 21:19:50 by abiru             #+#    #+#             */
/*   Updated: 2023/07/03 21:46:40 by youssef          ###   ########.fr       */
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

void	cleanup(t_scene_infn *scene)
{
	unsigned char	i;

	if (scene->content)
		free_split(scene->content);
	if (scene->minimap)
		free_split(scene->minimap);
	i = 0;
	while (i < 4)
	{
		if (scene->textures[i])
			free(scene->textures[i]);
		scene->textures[i] = 0;
		i++;
	}
}

void	init_player(t_vars *vars)
{
	vars->player.pos.x = vars->scene.s_pos_x + 0.5;
	vars->player.pos.y = vars->scene.s_pos_y + 0.5;
	vars->player.dir.x = 0;
	vars->player.dir.y = 0;
	vars->player.plane.x = 0;
	vars->player.plane.y = 0;
	if (vars->scene.s_orient == 'N')
	{
		vars->player.dir.y--;
		vars->player.plane.x = 0.66;
	}
	if (vars->scene.s_orient == 'E')
	{
		vars->player.dir.x++;
		vars->player.plane.y = 0.66;
	}
	if (vars->scene.s_orient == 'S')
	{
		vars->player.dir.y++;
		vars->player.plane.x = -0.66;
	}
	if (vars->scene.s_orient == 'W')
	{
		vars->player.dir.x--;
		vars->player.plane.y = -0.66;
	}
}

void	init_rays(t_vars *vars)
{
	vars->rays = malloc(WIN_WIDTH * sizeof(t_ray));
	if (!vars->rays)
		quit(vars);
}

void	init_keys(t_vars *vars)
{
	vars->keys.w = false;
	vars->keys.a = false;
	vars->keys.s = false;
	vars->keys.d = false;
	vars->keys.up = false;
	vars->keys.left = false;
	vars->keys.down = false;
	vars->keys.right = false;
}

int	main(int ac, char **av)
{
	t_vars	vars;

	if (!do_init_validation(ac, av, &vars.scene))
		return (1);
	init_struct(&vars.scene);
	if (!get_map_size(&vars.scene, av[1]))
		return (ft_putendl_fd(ERR, 2), ft_putendl_fd("Invalid map", 2), 1);
	if (!validate_map(&vars.scene))
	{
		close(vars.scene.map_fd);
		return (cleanup(&vars.scene), 1);
	}
	close(vars.scene.map_fd);
	if (vars.scene.counter != 7)
		return (cleanup(&vars.scene), ft_putendl_fd(ERR, 2),
			ft_putendl_fd(S_INC, 2), 1);
	init_window(&vars);
	init_player(&vars);
	init_rays(&vars);
	init_keys(&vars);
	draw_screen(&vars);
	draw_minimap(&vars);
	mlx_put_image_to_window(vars.mlx, vars.win, vars.image.img, 0, 0);
	mlx_key_hook(vars.win, key_up_hook, &vars);
	mlx_hook(vars.win, 2, 0, key_down_hook, &vars);
	mlx_hook(vars.win, RED_CROSS, 0, quit, &vars);
	mlx_loop_hook(vars.mlx, update_scene, &vars);
	mlx_loop(vars.mlx);
}
