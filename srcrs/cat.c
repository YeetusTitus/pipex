/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cat.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jforner <jforner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/02 14:36:26 by jforner           #+#    #+#             */
/*   Updated: 2021/12/16 13:30:00 by jforner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

char	*ft_strjoin(char *s1, char *s2)
{
	char	*str;
	int		len;
	int		i;
	int		j;

	len = (ft_strlen(s1) + ft_strlen(s2));
	str = malloc(len * sizeof(char) + 1);
	if (!str)
		return (NULL);
	i = 0;
	j = 0;
	while (s1[i] != 0)
	{
		str[i] = s1[i];
		i++;
	}
	while (s2[j] != 0)
	{
		str[i] = s2[j];
		i++;
		j++;
	}
	str[len] = 0;
	free(s1);
	return (str);
}

size_t	ft_strlen(char *str)
{
	int	count;

	count = 0;
	if (!str)
		return (0);
	while (str[count])
		count++;
	return (count);
}

int	ft_buftoline(char *buf, int fd, char **line)
{
	size_t		pos;
	int			error;

	error = 1;
	while (error)
	{
		if (error == -1)
			return (0);
		*line = ft_strjoin(*line, buf);
		pos = ft_strlen(*line);
		ft_memset(buf, 0, BUFFER_SIZE + 1);
		error = read(fd, buf, BUFFER_SIZE);
	}
	*line = ft_substr(*line, 0, pos);
	if (!*line || !*line[0])
		return (0);
	return (1);
}

char	*ft_cat(int fd)
{
	char	*line;
	char	buf[BUFFER_SIZE + 1];

	if (fd < 0)
		return (0);
	line = malloc(1 * sizeof(char));
	line[0] = 0;
	if (!(ft_buftoline(buf, fd, &line)))
	{
		if (line)
			free(line);
		return (NULL);
	}
	return (line);
}
