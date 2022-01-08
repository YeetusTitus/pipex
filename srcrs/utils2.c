/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jforner <jforner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/07 14:09:25 by jforner           #+#    #+#             */
/*   Updated: 2022/01/06 12:28:48 by jforner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"
/*
Desc: Do strstr but return 0 or 1
IN	: main string, searching string
OUT	: 1 or 0
*/

int	ft_sstr(char *str, char *search)
{
	int	i;
	int	j;

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
			return (1);
	}
	return (0);
}
/*
Desc: Do ft_sstr but only for the first character of str
IN	: main string, searching string
OUT	: 1 or 0
*/

int	ft_0sstr(char *str, char *search)
{
	int	i;

	if (str[0] == search[0])
	{
		i = -1;
		while (++i < (int)ft_strlen(search))
		{
			if (str[i] != search[i])
				break ;
		}
		if (i == (int)ft_strlen(search))
			return (1);
	}
	return (0);
}
/*
Desc: Give the lenght of a string or the lenght of till a certain character
IN	: string, peticular character
OUT : the length of the string
*/

int	rv_strchr(char	*str, char ch)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != ch)
		i++;
	return (i);
}
/*
Desc: Do substr whithout freeing the string s
IN	: main string, starting point of the string, the lenght of
the new string
OUT : string who begin with start and finish at len - 1 or
the end of s
*/

char	*ft_subs(char *s, unsigned int start, size_t len)
{
	char			*str;
	unsigned int	l;
	size_t			i;

	l = (unsigned int)ft_strlen(s);
	if (start >= l)
	{
		free(s);
		str = malloc(1 * sizeof(char));
		if (!str)
			return (str);
		str[0] = '\0';
		return (str);
	}
	if ((l - start) < len)
		len -= len - (l - start);
	str = malloc(len * sizeof(char) + 1);
	if (!str)
		return (str);
	i = 0;
	while (i < len)
		str[i++] = s[start++];
	str[i] = 0;
	return (str);
}
/*
Desc: Give the number of strings in a pointer of strings
IN	: pointer of strings
OUT : number of strings
*/

int	tab_len(char **tab)
{
	int	i;

	i = 0;
	while (tab[i] != NULL)
		i++;
	return (i);
}
