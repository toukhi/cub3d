/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abiru <abiru@student.42abudhabi.ae>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 21:18:47 by abiru             #+#    #+#             */
/*   Updated: 2023/06/02 16:10:48 by abiru            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H
# include "./libft/libft.h"
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


typedef struct scene_infn
{
	char *textures[4];
	int floor_clr[3];
	int ceil_clr[3];
	int is_duplicate[7];
	int counter;
	int **content;
	char **p_map;
	unsigned char s_orient;
	size_t size;
} t_scene_infn;

// parsing utils
void init_struct(t_scene_infn *scene);
void free_split(char **str);
size_t	get_split_size(char **str);
bool	is_space(char *str);
bool	check_duplicate(t_scene_infn *scene, unsigned short index);
bool	check_empty_field(char **str);


char **ft_ssplit(char const *s, char const *items);
bool	validate_map(int fd, t_scene_infn *scene);
bool	get_map_size(t_scene_infn *scene, int *map_fd, char *map);
bool	validate_texture(t_scene_infn *scene, char **str);
bool	get_colors(t_scene_infn *scene, char **str, char *val);
#endif