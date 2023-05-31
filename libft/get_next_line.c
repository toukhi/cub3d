/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abiru <abiru@student.42abudhabi.ae>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/27 19:04:20 by abiru             #+#    #+#             */
/*   Updated: 2023/05/31 23:06:42 by abiru            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*join_free(char *s1, char *s2)
{
	char	*tmp;

	if (!s1)
		tmp = ft_strdup(s2);
	else
	{
		tmp = ft_strjoin(s1, s2);
		free(s1);
	}
	return (tmp);
}

char *get_next_line(int fd)
{
	static char	*fd_table;
	int			size;
	char		*buffer;

	fd_table = 0;
	if (fd < 0 || fd > MAX_FD || read(fd, 0, 0) == -1)
		return (NULL);
	buffer = (char *)malloc(sizeof(char) * 2);
	if (!buffer)
		return (perror("malloc"), NULL);
	size = 1;
	while (size > 0)
	{
		size = read(fd, buffer, 1);
		if (size == 0)
			break ;
		buffer[1] = 0;
		fd_table = join_free(fd_table, buffer);
		if (ft_strchr(fd_table, '\n'))
			break ;
	}
	free(buffer);
	return (fd_table);
}



// int main()
// {
// 	int fd = open("test", O_RDONLY);
// 	char *str = get_next_line(fd);
// 	while (str)
// 	{
// 		printf("%s", str);
// 		free(str);
// 		str = get_next_line(fd);
// 	}
// 	free(str);
// }