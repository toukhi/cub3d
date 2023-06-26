
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

void	player_to_pixel(t_vector pos, t_vector *pixel) {
	pixel->x = pos.x * BLOCK_SIZE;
	pixel->y = pos.y * BLOCK_SIZE;
}

void	draw_minimap(t_vars *vars)
{
	size_t		i;
	size_t		j;
    t_vector	pixel_pos;

	// printf("player coordinates: x:%f, y:%f\n", vars->player.pos.x, vars->player.pos.y);
	// printf("player direction: x:%f, y:%f\n", vars->player.dir.x, vars->player.dir.y);
	
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
