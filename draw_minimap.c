
#include "cub3D.h"

int get_color(char c) {
    if (c == '1')
        return (GRAY);
    return (WHITE);
}

void	draw_square(t_data *data, t_vector pixel_pos, size_t size, int color)
{
	size_t i;
	size_t j;

	i = 0;
	while (i < size)
	{
		j = 0;
		while (j++ < size)
		{
			my_mlx_pixel_put(data, pixel_pos.x, pixel_pos.y, color);
			pixel_pos.x++;
		}
		pixel_pos.x -= j - 1;
		i++;
		pixel_pos.y++;
	}
}

// void	draw_circle(t_data *data, int x, int y, int color)
// {
// 	int radius;
// 	double PI;
// 	double angle;

// 	PI = 3.1415926535;
// 	radius = 4;
// 	while (radius > 0)
// 	{
// 		angle = 0;
// 		while (angle < 360)
// 		{
// 			my_mlx_pixel_put(data, x + radius * cos(angle * PI / 180), 
// 								y + radius * sin(angle * PI / 180), color);
// 			angle += 0.1;
// 		}
// 		radius--;
// 	}
	
// }

void	player_to_pixel(t_vector pos, t_vector *pixel) {
	pixel->x = pos.x * BLOCK_SIZE;
	pixel->y = pos.y * BLOCK_SIZE;
}

void	draw_minimap(t_vars *vars)
{
	size_t		i;
	size_t		j;
    t_vector	pixel_pos;

	i = 0;
    pixel_pos.y = 0;
	while (i < vars->scene.size)
	{
        pixel_pos.x = 0;
		j = 0;
		while (j < ft_strlen(vars->scene.minimap[i]))
		{
            draw_square(&vars->image, pixel_pos, BLOCK_SIZE, get_color(vars->scene.minimap[i][j]));
            pixel_pos.x += BLOCK_SIZE;
            j++;
		}
		i++;
        pixel_pos.y += BLOCK_SIZE;
	}
	player_to_pixel(vars->player.pos, &pixel_pos);
	draw_square(&vars->image, pixel_pos, 3, RED);
}
