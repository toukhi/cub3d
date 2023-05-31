/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abiru <abiru@student.42abudhabi.ae>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/23 19:48:32 by abiru             #+#    #+#             */
/*   Updated: 2023/05/31 16:57:53 by abiru            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	skip_spaces(const char *str)
{
	static int	i;

	i = 0;
	while (str[i] == ' ' || str[i] == '\t' || str[i] == '\n' || str[i] == '\v'
		|| str[i] == '\f' || str[i] == '\r')
		i++;
	return (i);
}

static int	cus_strlen(const char *str)
{
	int	i;
	int	j;

	j = 0;
	i = skip_spaces(str);
	while (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i] == '0')
		i++;
	while (str[i] != '\0')
	{
		if (str[i] >= '0' && str[i] <= '9')
			j++;
		else
			break ;
		i++;
	}
	return (j);
}

static size_t	find_end(char const *str)
{
	size_t	i;

	i = ft_strlen(str);
	--i;
	while (i >= 0 && str[i] && (str[i] == '\t' || str[i] == ' '))
		i--;
	return (i);
}
// static int	ft_sign(const char *str, int i)
// {
// 	if (str[i] == '+' || str[i] == '-')
// 	{
// 		if (str[i] == '-')
// 			return (-1);
// 	}
// 	return (1);
// }

static bool check_char(char const *str, size_t end)
{
	size_t	i;

	i = 0;
	while (i <= end && str + i && str[i] && (str[i] == ' ' || str[i] == '\t'))
		i++;
	if (str + i && str[i] && str[i] == '+')
		i++;
	while (i <= end && str + i && str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (true);
		i++;
	}
	return (false);
}

#include <stdio.h>
int	ft_atoi(const char *str)
{
	unsigned long long	result;
	int					i;
	size_t				end;

	result = 0;
	end = find_end(str);
	// printf("%s\n",str);
	if (check_char(str, end))
		return (-1);
	i = (int)skip_spaces(str);
	if (str[i] == '+')
		i++;
	if (cus_strlen(str) >= 4)
		return (-1);
	while (str[i] != '\0' && str[i] >= '0' && str[i] <= '9')
	{
		if (result >= 256)
			return (-1);
		result = (result * 10) + str[i] - '0';
		i++;
	}
	if (result >= 256)
		return (-1);
	return (result);
}

// #include <stdio.h>
// int main(int ac, char **av)
// {
// 	printf("%d\n", ft_atoi(av[1]));
// }