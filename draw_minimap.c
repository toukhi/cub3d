
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
		while (j < ft_strlen(vars->scene.minimap[i]))
		{
            draw_square(&vars->image, x, y, get_color(vars->scene.minimap[i][j]));
            x += 15;
            j++;
		}
		i++;
        y += 15;
	}
}