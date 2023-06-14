/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-touk <yel-touk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 21:18:47 by abiru             #+#    #+#             */
/*   Updated: 2023/06/14 15:38:33 by yel-touk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H
# include "./libft/libft.h"
# include "mlx/mlx.h"
# include <fcntl.h>
# include <stdbool.h>
# include <stdio.h>
# include <sys/stat.h>
# include <errno.h>

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

// window attributes
# define WIN_WIDTH 1200
# define WIN_HEIGHT 800

typedef struct scene_infn
{
	char			*textures[4];
	int				fc;
	int				cc;
	int				is_duplicate[7];
	int				counter;
	char			**content;
	char			**p_map;
	unsigned char	s_orient;
	size_t			size;
	int				map_fd;
}	t_scene_infn;

typedef struct s_data {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_data;

typedef struct s_vars {
	void	*mlx;
	void	*win;
	t_data	image;
}				t_vars;

// parsing utils
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

char	**ft_ssplit(char const *s, char const *items);
bool	validate_map(t_scene_infn *scene);
bool	get_map_size(t_scene_infn *scene, char *map);
bool	validate_texture(t_scene_infn *scene, char **str);
bool	get_colors(t_scene_infn *scene, char **str, char *val);
bool	validate_map_content(char *str, t_scene_infn *scene);
void	free_map(t_scene_infn *scene, int i);
void	cleanup(t_scene_infn *scene);

// execution utils
void	my_mlx_pixel_put(t_data *data, int x, int y, int color);
void	init_window(t_vars *vars);
int		quit(t_vars *vars, t_scene_infn *scene);

#endif