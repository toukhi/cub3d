/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abiru <abiru@student.42abudhabi.ae>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 21:18:47 by abiru             #+#    #+#             */
/*   Updated: 2023/05/30 19:48:53 by abiru            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H
# include "./libft/libft.h"
# include <fcntl.h>
# include <stdbool.h>
# include <stdio.h>

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
} t_scene_infn;

char **ft_ssplit(char const *s, char const *items);
#endif