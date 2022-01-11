/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jforner <jforner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/19 14:17:00 by jforner           #+#    #+#             */
/*   Updated: 2022/01/11 12:37:39 by jforner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

/*
Desc: Verify if the 2file are the same.
IN	: string 1, string 2
OUT	: 1 or 0
*/

void	create_temp(t_pipe *pipex)
{
	int		i;
	int		fd;
	char	*str;

	i = ft_strlen(pipex->flpath[1]);
	while (i > 0 && pipex->flpath[1][i - 1] != '/')
		--i;
	str = ft_subs(pipex->flpath[1], i, ft_strlen(pipex->flpath[1]));
	pipex->flpath[2] = sjoin("temp", str);
	free(str);
	pipex->op.filein = open(pipex->flpath[2], O_WRONLY | O_CREAT, 0644);
	fd = open(pipex->flpath[0], O_RDONLY);
	str = ft_cat(fd);
	ft_putstr_fd(str, pipex->op.filein);
	close(pipex->op.filein);
	pipex->op.filein = open(pipex->flpath[2], O_RDONLY);
	free(str);
}
