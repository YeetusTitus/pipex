/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jforner <jforner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/02 12:15:59 by jforner           #+#    #+#             */
/*   Updated: 2022/01/06 12:21:50 by jforner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/pipex.h"
#include "bonus/pipex_bonus.h"

int	main(int argc, char **argv, char **envp)
{
	t_pipe	pipex;
	pid_t	pid;

	if (!ft_parse(argc, argv, envp, &pipex))
		return (ft_puterror(argv, &pipex));
	mkarg(&pipex);
	pipe(pipex.pip);
	dup2(pipex.op.fileout, 1);
	close(pipex.op.fileout);
	if (!checkfork(&pid, &pipex))
		return (ft_puterror(argv, &pipex));
	if (pid == 0)
	{
		if (!core_pipex(argc - 4, &pipex))
		{
			ft_puterror(argv, &pipex);
			exit (1);
		}
		exit (0);
	}
	else
		wait(NULL);
	unlink(pipex.flpath[2]);
	return (1);
}
