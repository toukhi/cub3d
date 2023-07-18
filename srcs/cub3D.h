/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-touk <yel-touk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 21:18:47 by abiru             #+#    #+#             */
/*   Updated: 2023/07/18 19:17:48 by yel-touk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H
# include "../libft/libft.h"
# include "../mlx/mlx.h"
# include <math.h>
# include <fcntl.h>
# include <stdbool.h>
# include <stdio.h>
# include <sys/stat.h>
# include <errno.h>
# include <pthread.h>

//errors
# define ERR "Error"
# define EXT_ERR "Extra/little color information"
# define C_INV "Invalid ceiling color code"
# define F_INV "Invalid floor color code"
# define C_ABS "Color code not present"

// texture files not present
# define N_ERR "North texture file not present"
# define S_ERR "South texture file not present"
# define W_ERR "West texture file not present"
# define E_ERR "East texture file not present"

// texture file not having .xpm extension
# define N_INEXT "North texture file must have .xpm extension"
# define S_INEXT "South texture file must have .xpm extension"
# define W_INEXT "West texture file must have .xpm extension"
# define E_INEXT "East texture file must have .xpm extension"

// duplicate texture error messages
# define N_DUP "North texture duplicate found"
# define S_DUP "South texture duplicate found"
# define W_DUP "West texture duplicate found"
# define E_DUP "East texture duplicate found"

// extra information errors
# define N_EXT "Extra information detected on North texture line"
# define S_EXT "Extra information detected on South texture line"
# define W_EXT "Extra information detected on West texture line"
# define E_EXT "Extra information detected on East texture line"

// initial validation errors
# define ERR_EXTENSION "File extension must be .cub"
# define USG_ERR "Usage: ./cub3D map_file"
# define BAD_CHAR "Bad character found in map"
# define DUP_CHAR "Duplicate starting orientation found"
# define M_ORIENT "Starting orientation is missing"
# define M_OPEN	"Map has open walls"
# define S_INC "Scene is incomplete"
# define ERR_L_EMP "Empty line detected"
# define INV_COMMA "Extra / little commas found"
# define XPM "XPM file error"
# define SPRITE "Sprite does not exist"

// window attributes
# define WIN_WIDTH 1200
# define WIN_HEIGHT 850
# define MAP_WIDTH 375
# define MAP_HEIGHT 225
# define MAP_PADDING 10
# define RED_CROSS 17
# define BLOCK_SIZE 15

// key values
# define ESC 53
# define W 13
# define A 0
# define S 1
# define D 2
# define LEFT_ARROW 123
# define RIGHT_ARROW 124
# define R 15
# define X 7
# define M 46
# define B 11

// colors
# define CAMEL 0x00C19A6B
# define GRAY 0x00808080
# define WHITE 0x00FFFFFF
# define RED 0x00FF0000

//player attributes
# define TURN_ANGLE 0.0174533 // 1.0 deg in rad
# define WALK_SPEED 0.02
# define RUN_SPEED 0.05
# define SAFETY_DIST 0.1

typedef struct s_data
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}	t_data;

typedef struct s_texture
{
	t_data	img;
	int		width;
	int		height;
}	t_texture;

typedef struct scene_infn
{
	char			*textures[4];
	t_texture		no;
	t_texture		ea;
	t_texture		so;
	t_texture		we;
	t_texture		weapon1;
	t_texture		weapon2;
	t_texture		weapon3;
	int				fc;
	int				cc;
	int				is_duplicate[7];
	int				counter;
	char			**content;
	char			**minimap;
	unsigned char	s_orient;
	int				s_pos_x;
	int				s_pos_y;
	size_t			size;
	size_t			tmp_size;
	int				map_fd;
	size_t			longest;
}	t_scene_infn;

typedef struct s_vector
{
	double	x;
	double	y;
}	t_vector;

typedef struct s_ray
{
	t_vector	dir;
	t_vector	side_dist;
	t_vector	delta_dist;
	double		wall_dist;
	int			map_x;
	int			map_y;
	t_vector	step;
	int			hit;
	int			side;
	int			draw_start;
	int			draw_end;
	double		wall_x;
	t_texture	texture;
}	t_ray;

typedef struct s_player
{
	t_vector	pos;
	t_vector	dir;
	t_vector	plane;
}	t_player;

typedef struct sprite_vars
{
	int			*colors;
	int			color;
	int			start_x;
	int			start_y;
	int			tex_y;
	int			tex_x;
}	t_sp_vars;

typedef struct s_keys
{
	bool	w;
	bool	a;
	bool	s;
	bool	d;
	bool	left;
	bool	right;
	bool	run;
	bool	mouse;
	int		attack;
}	t_keys;

typedef struct s_vars
{
	void			*mlx;
	void			*win;
	t_data			image;
	t_data			image_map;
	t_scene_infn	scene;
	t_player		player;
	t_ray			*rays;
	t_keys			keys;
	t_vector		mouse_pos;
}	t_vars;

// parsing utils
void	*make_sound(void *vars);
void	init_scene(t_vars *vars);
void	free_split(char **str);
size_t	get_split_size(char **str);
bool	is_space(char *str);
bool	check_duplicate(t_scene_infn *scene, unsigned short index);
bool	check_empty_field(char **str);
size_t	find_row_size(char *arr);
bool	check_texture(char *str, char *msg);
bool	search_bad_chars(char **arr, t_scene_infn *scene);
bool	check_borders(t_scene_infn *scene, char **arr, int i, int j);
size_t	get_real_size(t_scene_infn *scene);
void	update_values(t_vars *vars, short index, char **str);
bool	check_sprite(t_vars *vars);

char	**ft_ssplit(char const *s, char const *items);
bool	validate_map(t_vars *vars);
bool	get_map_size(t_scene_infn *scene, char *map);
bool	validate_texture(t_vars *vars, char **str);
bool	get_colors(t_scene_infn *scene, char **str, char *val);
bool	validate_map_content(char *str, t_scene_infn *scene);
void	free_map(t_scene_infn *scene, int i);
void	cleanup(t_vars *vars);
void	set_longest_line(t_scene_infn *scene);
bool	create_minimap(t_scene_infn *scene);
void	free_mem_parsing(char *str, char **str2, char *str3);

// execution utils
void	init_keys(t_vars *vars);
void	init_rays(t_vars *vars);
void	init_player(t_vars *vars);

void	my_mlx_pixel_put(t_data *data, int x, int y, int color);
void	init_window(t_vars *vars);
void	redraw_image(t_vars *vars);
int		quit(t_vars *vars);

void	set_keys(int key, t_keys *keys, bool status);
int		key_up_hook(int keycode, t_vars *vars);
int		key_down_hook(int keycode, t_vars *vars);
int		mouse_move_hook(int x, int y, t_vars *vars);
void	draw_minimap(t_vars *vars);
void	draw_screen(t_vars *vars);
void	draw_sprite(t_vars *vars);

void	set_side_dist(t_ray *ray_p, t_player p);
void	set_ray_p(t_ray **ray_p, int ray_num, t_vars *vars);
void	set_wall_dist(t_ray **ray_p);
void	set_texture(t_ray **ray_p, t_vars *vars);
void	set_wall_x(t_ray **ray_p, t_vars *vars);

void	dda(t_ray *ray_p, char **map);
void	draw_ver_line(t_data *data, int x, t_vector y, int color);
void	draw_background(t_ray **ray_p, t_vars *vars,
			int wall_height, int ray_num);
void	draw_wall(t_ray *ray_p, t_vars *vars, int pixel_x, int wall_height);
void	draw_screen(t_vars *vars);
int		update_scene(t_vars *vars);
bool	is_collision_x(t_vars *vars, double move_speed, int key);
bool	is_collision_y(t_vars *vars, double move_speed, int key);
void	move_forward(t_vars *vars, double move_speed);
void	move_backward(t_vars *vars, double move_speed);
void	move_right(t_vars *vars, double move_speed);
void	move_left(t_vars *vars, double move_speed);
void	move_player(t_vars *vars);
void	rotate_player(t_vector *dir, t_vector *plane, t_keys *keys);
void	rotate_player_mouse(int key, t_vars *vars);
void	*make_sound(void *vars);

#endif