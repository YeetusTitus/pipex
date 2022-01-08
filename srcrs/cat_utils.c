/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cat_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jforner <jforner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/02 17:31:32 by jforner           #+#    #+#             */
/*   Updated: 2021/12/02 17:55:14 by jforner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

char	*ft_fullstr(char *s, unsigned int start, size_t len, char *str)
{
	size_t	i;

	i = 0;
	while (i < len)
	{
		str[i] = s[start];
		i++;
		start++;
	}
	str[i] = 0;
	free(s);
	return (str);
}

char	*ft_substr(char *s, unsigned int start, size_t len)
{
	char			*str;
	unsigned int	l;

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
	str = ft_fullstr(s, start, len, str);
	return (str);
}

void	*ft_memset(void *str, char c, size_t n)
{
	unsigned int	i;
	unsigned char	*v;

	v = (unsigned char *)str;
	i = 0;
	while (i < n)
	{
		v[i] = c;
		i++;
	}
	return (v);
}
