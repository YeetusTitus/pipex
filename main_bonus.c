/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jforner <jforner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/20 18:35:30 by jforner           #+#    #+#             */
/*   Updated: 2022/01/06 12:31:04 by jforner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bonus/pipex_bonus.h"

int	main(int argc, char **argv, char **envp)
{
	t_pipe	pipex;
	pid_t	pid;

	if (!ft_parse_here(argc, argv, envp, &pipex))
		return (ft_puterror(argv, &pipex));
	if (pipex.bonus.ishere)
		heredoc(&pipex);
	mkarg(&pipex);
	pipe(pipex.pip);
	dup2(pipex.op.fileout, 1);
	close(pipex.op.fileout);
	checkfork(&pid, &pipex);
	if (pid == 0)
	{
		if (!core_pipex(argc - (4 + pipex.bonus.ishere), &pipex))
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
