/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jforner <jforner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/14 17:48:00 by jforner           #+#    #+#             */
/*   Updated: 2022/01/06 12:36:28 by jforner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

/*
Desc: Do strcmp, but only return 0 if they are different and 1 if they alike
IN	: string 1, string 2
OUT	: 1 or 0
*/

int	ft_strcmp(const char *s1, const char *s2)
{
	int		t1;
	int		t2;
	size_t	count;

	count = 0;
	t1 = 0;
	t2 = 0;
	while (s1[count] && s2[count])
	{
		t1 = (unsigned char)s1[count];
		t2 = (unsigned char)s2[count];
		if ((unsigned char)s1[count] != (unsigned char)s2[count])
			return (0);
		count++;
	}
	t1 = (unsigned char)s1[count];
	t2 = (unsigned char)s2[count];
	if (t1 != t2)
		return (0);
	return (1);
}

char	*reanding0(t_pipe *pipex)
{
	char	buf[2];
	char	*str;
	char	*line;
	char	*cmp;

	str = ft_calloc(1, 1);
	line = ft_calloc(1, 1);
	cmp = sjoin(pipex->bonus.heredoc, "\n");
	while (!ft_strcmp(line, cmp))
	{
		str = ft_strjoin(str, line);
		free(line);
		line = ft_calloc(1, 1);
		ft_memset(buf, 0, 2);
		ft_putstr_fd("heredoc>", 0);
		while (buf[0] != '\n')
		{
			read(0, buf, 1);
			line = ft_strjoin(line, buf);
		}
	}
	free(cmp);
	free(line);
	return (str);
}

void	heredoc(t_pipe *pipex)
{
	char	*str;
	int		fd;

	str = reanding0(pipex);
	fd = open("here_doc", O_WRONLY | O_CREAT, 0644);
	pipex->flpath[2] = ft_subs("here_doc", 0, ft_strlen("here_doc"));
	ft_putstr_fd(str, fd);
	free(str);
	close(fd);
	pipex->op.filein = open(pipex->flpath[2], O_RDONLY);
}
