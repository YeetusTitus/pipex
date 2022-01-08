/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   complete.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jforner <jforner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/16 19:36:00 by jforner           #+#    #+#             */
/*   Updated: 2022/01/06 12:23:56 by jforner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

char	**ft_tabdup(char **tab)
{
	char	**dest;
	int		i;

	dest = (char **)malloc(tab_len(tab) * sizeof(char *) + 1);
	i = -1;
	while (++i < tab_len(tab))
		dest[i] = ft_subs(tab[i], 0, ft_strlen(tab[i]));
	ft_malloc_error(tab, tab_len(tab) - 1);
	dest[i] = NULL;
	return (dest);
}

void	jointab(t_pipe *pipex, int itab, int min, int *max)
{
	int		i;

	i = *max;
	while (i - min > 0)
	{
		pipex->cmdtab[itab][i - 1] = ft_strjoin(ft_strjoin(
					pipex->cmdtab[itab][i - 1], " "),
				pipex->cmdtab[itab][i]);
		free(pipex->cmdtab[itab][i]);
		pipex->cmdtab[itab][i] = NULL;
		i--;
	}
	pipex->cmdtab[itab] = ft_tabdup(pipex->cmdtab[itab]);
	i = -1;
	while (pipex->cmdtab[0][++i] != NULL)
	{
		ft_putstr_fd(pipex->cmdtab[0][i], 2);
		ft_putchar_fd('\n', 2);
	}
	*max = min;
}

int	ft_countchr(char *str, char ch)
{
	int	count;
	int	i;

	count = 0;
	i = -1;
	while (str[++i])
		if (str[i] == ch)
			count++;
	return (count);
}

void	mkarg(t_pipe *pipex)
{
	int		i;
	int		j;
	int		k;
	char	close;

	j = -1;
	while (++j < pipex->argc - 3)
	{
		close = '\0';
		i = -1;
		while (pipex->cmdtab[j][++i] != NULL)
		{
			k = i;
			if (!close && ft_countchr(pipex->cmdtab[j][i], '"') % 2 == 1)
				close = '"';
			if (!close && ft_countchr(pipex->cmdtab[j][i], 0x27) % 2 == 1)
				close = 0x27;
			if (close)
				while (pipex->cmdtab[j][++k] != NULL)
					if (ft_countchr(pipex->cmdtab[j][k], close) % 2 == 1)
						jointab(pipex, j, i, &k);
		}
	}
}
