
#include "cub3D.h"

int get_color(char c) {
    if (c == '1')
        return (GRAY);
    return (WHITE);
}

void	draw_square(t_data *data, t_vector pos, size_t size, int color)
{
	size_t i;
	size_t j;

	i = 0;
	while (i < size)
	{
		j = 0;
		while (j++ < size)
		{
			my_mlx_pixel_put(data, pos.x, pos.y, color);
			pos.x++;
		}
		pos.x -= j - 1;
		i++;
		pos.y++;
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

void	draw_minimap(t_vars *vars)
{
	size_t		i;
	size_t		j;
    t_vector	pos;

	i = 0;
    pos.y = 0;
	while (i < vars->scene.size)
	{
        pos.x = 0;
		j = 0;
		while (j < ft_strlen(vars->scene.minimap[i]))
		{
            draw_square(&vars->image, pos, 15, get_color(vars->scene.minimap[i][j]));
            pos.x += 15;
            j++;
		}
		i++;
        pos.y += 15;
	}
	draw_square(&vars->image, vars->player.pos, 3, RED);
	// draw_circle(&vars->image, (vars->player.pos.x + 1) * 15, (vars->player.pos.y + 1) * 15, RED);
}