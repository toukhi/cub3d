/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abiru <abiru@student.42abudhabi.ae>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/02 23:24:04 by abiru             #+#    #+#             */
/*   Updated: 2023/06/05 11:19:22 by abiru            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

char	**populate_map_arr(char *str, t_scene_infn *scene)
{
	size_t	i;
	char	*str2;
	char	**arr;

	arr = (char **)malloc(sizeof(char *) * (scene->size + 1));
	if (!arr)
		return (ft_putendl_fd(ERR, 2), perror("Malloc"), NULL);
	i = 0;
	while (str)
	{
		str2 = ft_strtrim(str, "\n");
		free(str);
		arr[i++] = str2;
		str = get_next_line(scene->map_fd);
	}
	arr[i] = 0;
	if (str)
		free(str);
	return (arr);
}

void	check_recursively(char **arr, int i, int j, bool *flag)
{
	if (i < 0 || j < 0 || !arr[i] || j >= (int)find_row_size(arr[i])
		|| arr[i][j] == '1')
		return ;
	else if (arr[i][j] != '1' && arr[i][j] != ' ' && arr[i][j] != '\t')
	{
		*flag = false;
		return ;
	}
	arr[i][j] = '1';
	check_recursively(arr, i - 1, j, flag);
	check_recursively(arr, i + 1, j, flag);
	check_recursively(arr, i, j - 1, flag);
	check_recursively(arr, i, j + 1, flag);
}

/*
	- Map is invalid if:
	-> if the 1st column's value in a row isn't 1, ' ', or '\t'
	-> if there is at least 1 item with a value different from 
	1, ' ', & '\t' on the 1st & last row
	-> if a space char is found on a column, and the column is
		found on the 1st or last row 
		or 1st index or last index of any row,
		or at any index on the array & the row above or below it has fewer items
		compared to the current index -> recursively checks for open walls
*/

bool	check_open_wall(t_scene_infn *scene, char **arr)
{
	int		i;
	int		j;
	bool	flag;

	i = -1;
	flag = true;
	while (arr[++i])
	{
		j = -1;
		while (arr[i][++j])
		{
			if (check_borders(scene, scene->content, i, j))
				return (false);
			if ((i == 0 || i == (int)scene->size - 1 || j == 0
					|| !arr[i][j + 1] || (int)find_row_size(arr[i + 1]) <= j
				|| (int)find_row_size(arr[i - 1]) <= j)
					&& (arr[i][j] == ' ' || arr[i][j] == '\t'))
			{
				check_recursively(arr, i, j, &flag);
				if (!flag)
					return (ft_putendl_fd(ERR, 2), ft_putendl_fd(M_OPEN, 2), 1);
			}
		}
	}
	return (false);
}

bool	construct_map(char **arr, t_scene_infn *scene)
{
	size_t	i;

	i = 0;
	if (!arr)
		return (false);
	scene->content = (char **)malloc(sizeof(char *) * (scene->size + 1));
	if (!scene->content)
		return (ft_putendl_fd(ERR, 2), perror("Malloc"), false);
	while (arr[i])
	{
		scene->content[i] = ft_strdup(arr[i]);
		i++;
	}
	scene->content[i] = 0;
	return (true);
}

/*
	// populate map array
	// check for illegal chars (char except 1, 0, N, S, E, W, ' ', '\t', '\n')
	// check for multiple starting values (duplicate starting values)
	// check for open wall
*/
bool	validate_map_content(char *str, t_scene_infn *scene)
{
	char	**arr;

	arr = populate_map_arr(str, scene);
	if (!arr)
		return (false);
	if (search_bad_chars(arr, scene))
		return (free_split(arr), false);
	if (!construct_map(arr, scene))
		return (free_split(arr), false);
	if (check_open_wall(scene, arr))
		return (free_split(arr), free_map(scene, -1), false);
	free_split(arr);
	scene->counter++;
	return (true);
}
