/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abiru <abiru@student.42abudhabi.ae>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 15:45:33 by yel-touk          #+#    #+#             */
/*   Updated: 2023/07/18 12:52:29 by abiru            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *) dst = color;
}

void	init_window(t_vars *vars)
{
	vars->win = mlx_new_window(vars->mlx, WIN_WIDTH, WIN_HEIGHT, "cub3d");
	vars->image.img = mlx_new_image(vars->mlx, WIN_WIDTH, WIN_HEIGHT);
	vars->image.addr = mlx_get_data_addr(vars->image.img,
			&vars->image.bits_per_pixel, &vars->image.line_length,
			&vars->image.endian);
	vars->image_map.img = mlx_new_image(vars->mlx, MAP_WIDTH, MAP_HEIGHT);
	vars->image_map.addr = mlx_get_data_addr(vars->image_map.img,
			&vars->image_map.bits_per_pixel, &vars->image_map.line_length,
			&vars->image_map.endian);
}

void	redraw_image(t_vars *vars)
{
	mlx_clear_window(vars->mlx, vars->win);
	draw_screen(vars);
	draw_minimap(vars);
	mlx_put_image_to_window(vars->mlx, vars->win, vars->image.img, 0, 0);
	mlx_put_image_to_window(vars->mlx, vars->win, vars->image_map.img,
		MAP_PADDING, MAP_PADDING);
}

int	quit(t_vars *vars)
{
	pthread_mutex_destroy(&vars->checker);
	pthread_join(vars->id, 0);
	cleanup(vars);
	if (vars->rays)
		free(vars->rays);
	mlx_destroy_image(vars->mlx, vars->image_map.img);
	mlx_destroy_image(vars->mlx, vars->image.img);
	mlx_destroy_window(vars->mlx, vars->win);
	free(vars->mlx);
	exit(EXIT_SUCCESS);
}
