/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youssef <youssef@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 21:18:47 by abiru             #+#    #+#             */
/*   Updated: 2023/07/13 23:21:17 by youssef          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H
# include "./libft/libft.h"
# include "mlx/mlx.h"
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
# define RED_CROSS 17
# define BLOCK_SIZE 15

// key values
# define ESC 53
# define W 13
# define A 0
# define S 1
# define D 2
# define UP_ARROW 126
# define LEFT_ARROW 123
# define DOWN_ARROW 125
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
	t_texture		NO;
	t_texture		EA;
	t_texture		WE;
	t_texture		SO;
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
	t_vector	sideDist;
	t_vector	deltaDist;
	double		wallDist;
	int			mapX;
	int			mapY;
	t_vector	step;
	int			hit;
	int			side;
}	t_ray;


typedef struct s_player
{
	t_vector	pos;
	t_vector	dir;
	t_vector	plane;
}	t_player;

typedef struct s_keys
{
	bool	w;
	bool	a;
	bool	s;
	bool	d;
	bool	left;
	bool	down;
	bool	right;
	bool	up;
	bool	run;
	bool	mouse;
	bool	map;
	int		attack;
}	t_keys;

typedef struct s_vars
{
	void			*mlx;
	void			*win;
	t_data			image;
	t_scene_infn	scene;
	t_player		player;
	t_ray			*rays;
	t_keys			keys;
	t_vector		mouse_pos;
	pthread_t		id;
	pthread_mutex_t	checker;
	int				cur_key;
	bool			screen;
}	t_vars;

// parsing utils
void	*make_sound(void *vars);
void	init_struct(t_scene_infn *scene);
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

char	**ft_ssplit(char const *s, char const *items);
bool	validate_map(t_vars *vars);
bool	get_map_size(t_scene_infn *scene, char *map);
bool	validate_texture(t_vars *vars, char **str);
bool	get_colors(t_scene_infn *scene, char **str, char *val);
bool	validate_map_content(char *str, t_scene_infn *scene);
void	free_map(t_scene_infn *scene, int i);
void	cleanup(t_scene_infn *scene);
void	set_longest_line(t_scene_infn *scene);
bool	create_minimap(t_scene_infn *scene);

bool	check_sprite(t_vars *vars);

// execution utils
void	my_mlx_pixel_put(t_data *data, int x, int y, int color);
void	init_window(t_vars *vars);
void	redraw_image(t_vars *vars);
int		quit(t_vars *vars);

int		key_up_hook(int keycode, t_vars *vars);
int		key_down_hook(int keycode, t_vars *vars);
int		mouse_move_hook(int x, int y, t_vars *vars);
void	draw_minimap(t_vars *vars);
void	draw_screen(t_vars *vars);

int		update_scene(t_vars *vars);
void	attack(t_vars *vars);

#endif