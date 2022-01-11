/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jforner <jforner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/02 12:50:53 by jforner           #+#    #+#             */
/*   Updated: 2022/01/11 12:39:45 by jforner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

void	ft_putchar_fd(char c, int fd)
{
	write (fd, &c, 1);
}

void	ft_putstr_fd(char *s, int fd)
{
	if (!s || s == NULL)
		ft_putchar_fd (0, fd);
	else
	{
		while (*s)
		{
			ft_putchar_fd(*s, fd);
			s++;
		}
	}
}
/*
Return the concatenation of the string S1 
and the string S2 without freeing something
*/

char	*sjoin(char *s1, char *s2)
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
	return (str);
}

void	*ft_calloc(size_t nmemb, size_t size)
{
	size_t	i;
	void	*array;

	i = 0;
	array = malloc(nmemb * size);
	if (!array)
		return (NULL);
	ft_memset(array, 0, nmemb);
	return (array);
}

char	*str_next_str(char *str, char *search)
{
	int		i;
	int		j;

	i = -1;
	while (str[++i])
	{
		j = i;
		while (j - i < (int)ft_strlen(search))
		{
			if (str[j] != search[j - i])
				break ;
			j++;
		}
		if (j - i == (int)ft_strlen(search))
		{
			if (!str[j])
				return ("\0");
			else
				return (&str[j]);
		}
	}
	return (NULL);
}
