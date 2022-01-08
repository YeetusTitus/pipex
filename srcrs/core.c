/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   core.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jforner <jforner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/08 18:55:21 by jforner           #+#    #+#             */
/*   Updated: 2022/01/06 11:23:50 by jforner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

/*
Desc: Create a fork and check if it doesn't bring problems
IN	: array of pipe structure
OUT : 0 or 1
*/
int	checkfork(pid_t	*pid, t_pipe *pipex)
{
	*pid = fork();
	if (errno != 0)
		errno = 0;
	if (*pid < 0)
	{
		pipex->error = 'h';
		return (0);
	}
	return (1);
}

int	pipemanagement(int ncmds, int input[2], t_pipe *pipex)
{
	int	fd;

	if (ncmds == 0)
	{
		fd = dup2(pipex->op.filein, 0);
		close(pipex->op.filein);
	}
	else
	{
		fd = dup2(input[0], 0);
		close(input[0]);
	}
	if (fd < 0)
		return (0);
	if (ncmds > 0)
		close(input[1]);
	return (1);
}

int	core_pipex(int ncmds, t_pipe *pipex)
{
	pid_t	pid;
	int		input[2];

	if (ncmds < 0)
		return (1);
	if (pipe(input) != 0 || checkfork(&pid, pipex) < 0
		|| (pid == 0 && !pipeline(ncmds - 1, input, pipex)))
		return (0);
	if (!pipemanagement(ncmds, input, pipex))
		return (0);
	if (pid > 0)
		execve(pipex->cmdtab[ncmds][0], pipex->cmdtab[ncmds], NULL);
	if (errno != 0)
		return (0);
	return (1);
}

int	pipeline(int ncmds, int output[2], t_pipe *pipex)
{
	int	fd;

	fd = dup2(output[1], 1);
	if (fd < 0)
		return (0);
	if (!core_pipex(ncmds, pipex))
		return (0);
	return (1);
}
