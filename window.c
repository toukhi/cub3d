/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youssef <youssef@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 15:45:33 by yel-touk          #+#    #+#             */
/*   Updated: 2023/06/24 15:04:06 by youssef          ###   ########.fr       */
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
	vars->mlx = mlx_init();
	vars->win = mlx_new_window(vars->mlx, WIN_WIDTH, WIN_HEIGHT, "cub3d");
	vars->image.img = mlx_new_image(vars->mlx, WIN_WIDTH, WIN_HEIGHT);
	vars->image.addr = mlx_get_data_addr(vars->image.img,
			&vars->image.bits_per_pixel, &vars->image.line_length,
			&vars->image.endian);
}

void	redraw_image(t_vars *vars)
{
	mlx_destroy_image(vars->mlx, vars->image.img);
	vars->image.img = mlx_new_image(vars->mlx, WIN_WIDTH, WIN_HEIGHT);
	vars->image.addr = mlx_get_data_addr(vars->image.img,
			&vars->image.bits_per_pixel, &vars->image.line_length,
			&vars->image.endian);
	draw_minimap(vars);
	mlx_put_image_to_window(vars->mlx, vars->win, vars->image.img, 0, 0);
}

int	quit(t_vars *vars)
{
	cleanup(&vars->scene);
	if (vars->rays)
		free(vars->rays);
	mlx_destroy_image(vars->mlx, vars->image.img);
	mlx_destroy_window(vars->mlx, vars->win);
	exit(EXIT_SUCCESS);
}
