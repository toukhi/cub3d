
#include "cub3D.h"

int get_color(char c) {
    if (c == '1')
        return (GRAY);
    return (WHITE);
}

void	draw_square(t_data *data, int x, int y, int color)
{
	int	a;
	int i;
	int j;

	a = 15;
	i = 0;
	while (i < a)
	{
		j = 0;
		while (j++ < a)
		{
			my_mlx_pixel_put(data, x, y, color);
			x++;
		}
		x -= j - 1;
		i++;
		y++;
	}
}

void	draw_minimap(t_vars *vars)
{
	// draw_square(&vars->image, 0, 0, GRAY);
	size_t	i;
	size_t	j;
    int x;
    int y;

	i = 0;
    y = 0;
	while (i < vars->scene.size)
	{
        x = 0;
		j = 0;
		while (j < ft_strlen(vars->scene.content[i]))
		{
            draw_square(&vars->image, x, y, get_color(vars->scene.content[i][j]));
            x += 15;
            j++;
		}
		i++;
        y += 15;
	}

	// int map_width;
	// int	map_height;
	
	// map_width = WIN_WIDTH;
	// map_height = WIN_HEIGHT / vars.scene.size;
}