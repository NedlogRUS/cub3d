/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apanikov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 14:38:24 by apanikov          #+#    #+#             */
/*   Updated: 2023/04/04 14:38:46 by apanikov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*read_line(int fd, char *buffer)
{
	int		i;
	char	buf[BUFFER_SIZE + 1];
	char	*tmp;

	i = 1;
	while (!ft_strchr_gnl (buffer, '\n') && i > 0)
	{
		i = read(fd, buf, BUFFER_SIZE);
		if (i < 0)
		{
			free (buffer);
			return (NULL);
		}
		buf[i] = '\0';
		tmp = buffer;
		buffer = ft_strjoin_gnl(buffer, buf);
		free(tmp);
	}
	return (buffer);
}

char	*rebuffer(char *buffer)
{
	char	*tmp;
	int		len;

	if (ft_strchr_gnl(buffer, '\n'))
	{
		tmp = buffer;
		len = ft_strlen_gnl(ft_strchr_gnl(buffer, '\n') + 1);
		buffer = ft_substr_gnl(buffer, ft_strlen_gnl(buffer) - len, len);
		free (tmp);
		tmp = NULL;
	}
	else
	{
		free(buffer);
		return (NULL);
	}
	return (buffer);
}

char	*ft_out(char *buffer)
{
	char	*out;
	int		lk;

	lk = ft_strlen_gnl(buffer);
	if (ft_strchr_gnl(buffer, '\n'))
		out = ft_substr_gnl(buffer, 0, \
		lk - ft_strlen_gnl(ft_strchr_gnl(buffer, '\n') + 1));
	else
		out = ft_strdup_gnl(buffer);
	return (out);
}

char	*get_next_line(int fd)
{
	static char	*buffer = NULL;
	char		*out;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
		return (NULL);
	buffer = read_line(fd, buffer);
	if (buffer[0] == '\0')
	{
		free(buffer);
		buffer = NULL;
		return (NULL);
	}
	out = ft_out(buffer);
	buffer = rebuffer(buffer);
	return (out);
}

// int main()
// {
//     int fd;
//     char *out;

//     fd = open("gnl.txt", O_RDONLY);
//     out = get_next_line(fd);
// 	printf("%s", out);
// 	//out = get_next_line(fd);
// 	free(out);
// 	system("leaks a.out");
// 	//printf("%s\n", out);
// }