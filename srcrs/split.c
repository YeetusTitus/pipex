/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jforner <jforner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/07 12:47:14 by jforner           #+#    #+#             */
/*   Updated: 2021/12/17 20:19:06 by jforner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

void	ft_malloc_error(char **tab, int size)
{
	while (size-- > 0)
		free(tab[size]);
	free(tab);
}

int	ft_splitage(char *s, char c, char **tab, unsigned int nb_word)
{
	int	crnt_word;
	int	len;

	crnt_word = -1;
	len = 0;
	while (++crnt_word < (int)nb_word)
	{
		s += len;
		len = 0;
		while (s[len] && s[len] == c)
			len++;
		s += len;
		len = 0;
		while (s[len] && s[len] != c)
			len++;
		if (s[len - 1])
			tab[crnt_word] = ft_subs(s, 0, len);
		if (!(tab[crnt_word]))
		{
			while (crnt_word-- > 0)
				free(tab[crnt_word]);
			return (0);
		}
	}
	return (1);
}

int	ft_tablen(char *str, char sep, char ***tab, unsigned int *nb_word)
{
	int	i;

	i = 0;
	(*nb_word) = 0;
	while (str[i])
	{
		while (str[i] && str[i] == sep)
			i++;
		if (str[i])
			(*nb_word)++;
		while (str[i] && str[i] != sep)
			i++;
	}
	(*tab) = ft_calloc((*nb_word) + 1, sizeof(char *));
	if (!(*tab))
		return (0);
	return (1);
}

char	**ft_split(char *s, char c)
{
	char			**tab;
	unsigned int	nb_word;

	if (!(ft_tablen(s, c, &tab, &nb_word)))
		return (NULL);
	if (!(ft_splitage(s, c, tab, nb_word)))
	{
		free(tab);
		return (NULL);
	}
	tab[nb_word] = NULL;
	return (tab);
}
