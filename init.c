#include "cub3D.h"

void	set_zero(t_vector *vector)
{
	vector->x = 0;
	vector->y = 0;
}

void	init_player(t_vars *vars)
{
	vars->player.pos.x = vars->scene.s_pos_x + 0.5;
	vars->player.pos.y = vars->scene.s_pos_y + 0.5;
	set_zero(&vars->player.dir);
	set_zero(&vars->player.plane);
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
	vars->keys.run = false;
	vars->keys.mouse = false;
	vars->keys.attack = false;
	vars->cur_key = -1;
	vars->screen = true;
}
