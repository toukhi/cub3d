/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ssplit.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abiru <abiru@student.42abudhabi.ae>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 11:23:00 by abiru             #+#    #+#             */
/*   Updated: 2023/06/05 10:53:08 by abiru            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"
#include <stdio.h>
#include <stdbool.h>

static size_t	ft_count(char const *s, char const *items)
{
	bool	flag;
	size_t	count;
	size_t	i;

	flag = false;
	count = 0;
	i = 0;
	while (s + i && s[i])
	{
		if (!ft_strchr(items, s[i]) && !flag)
		{
			flag = true;
			count++;
		}
		else if (ft_strchr(items, s[i]))
			flag = false;
		i++;
	}
	return (count);
}

static int	find_end(size_t start, char const *s, char const *c)
{
	while (s[start] && !ft_strchr(c, s[start]))
		start++;
	return (start);
}

static char	*ft_cpy(const char *s, char *dst, size_t start, size_t end)
{
	int	i;

	i = 0;
	while (start < end)
		dst[i++] = s[start++];
	dst[i] = '\0';
	return (dst);
}

static char	**split_str(char **res, char *ptr, char const *s, char const *items)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (i < ft_count(s, items))
	{
		while (ft_strchr(items, s[j]))
			j++;
		ptr = (char *)malloc(sizeof(*s) * (find_end(j, s, items) - j + 1));
		if (!ptr)
		{
			i = 0;
			while (res[i])
				free(res[i++]);
			free(res);
			return (NULL);
		}
		ft_cpy(s, ptr, j, find_end(j, s, items));
		j = find_end(j, s, items);
		res[i++] = ptr;
	}
	return (res);
}

char	**ft_ssplit(char const *s, char const *items)
{
	char	*ptr;
	char	**res;

	if (!items || !s)
		return (0);
	res = (char **)malloc(sizeof(char *) * (ft_count(s, items) + 1));
	if (!res)
		return (perror("Malloc"), NULL);
	ptr = 0;
	if (!split_str(res, ptr, s, items))
		return (free(res), NULL);
	res[ft_count(s, items)] = 0;
	return (res);
}
