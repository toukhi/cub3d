/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abiru <abiru@student.42abudhabi.ae>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 21:18:47 by abiru             #+#    #+#             */
/*   Updated: 2023/05/29 12:58:55 by abiru            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H
# include "./libft/libft.h"

typedef struct scene_infn
{
	int north_tf;
	int south_tf;
	int west_tf;
	int east_tf;

	int floor_clr;
	int ceil_clr;
} t_scene_infn;

char **ft_ssplit(char const *s, char const *items);
#endif