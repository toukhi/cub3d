/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abiru <abiru@student.42abudhabi.ae>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/16 15:24:21 by abiru             #+#    #+#             */
/*   Updated: 2023/06/16 15:27:33 by abiru            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

bool	create_minimap(t_scene_infn *scene)
{
	scene->minimap = (char **)malloc(sizeof(char *) * (scene->size + 1));
	if (!scene->minimap)
		return (ft_putendl_fd(ERR, 2), ft_putendl_fd("ma"))
}