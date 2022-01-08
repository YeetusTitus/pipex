/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jforner <jforner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/14 14:33:00 by jforner           #+#    #+#             */
/*   Updated: 2022/01/06 12:39:27 by jforner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../bonus/pipex_bonus.h"

void	fullparse_bonus(t_pipe *pipex, int argc, char **argv)
{
	int	i;

	i = 0;
	while ((i < argc - 3 && pipex->bonus.ishere == 0)
		|| (i < argc - 4 && pipex->bonus.ishere == 1))
	{
		free(pipex->cmdtab[i][0]);
		pipex->cmdtab[i][0] = ft_subs(pipex->cmdpath[i], 0,
				ft_strlen(pipex->cmdpath[i]));
		i++;
	}
	pipex->argc = argc;
	pipex->flpath[1] = ft_subs(argv[argc - 1], 0, ft_strlen(argv[argc - 1]));
	if (pipex->bonus.ishere)
	{
		pipex->bonus.heredoc = ft_subs(argv[2], 0, ft_strlen(argv[2]));
		pipex->op.fileout = open(pipex->flpath[1], O_WRONLY | O_APPEND);
	}
	else
	{
		pipex->flpath[0] = ft_subs(argv[1], 0,
				ft_strlen(argv[1]));
		create_temp(pipex);
		pipex->op.fileout = open(pipex->flpath[1], O_WRONLY | O_TRUNC);
	}
}

int	file_verificator(int i, char **argv, int argc, t_pipe *pipex)
{
	if (i == 1 && !pipex->bonus.ishere)
	{
		if (access(argv[i], R_OK) == -1)
		{
			pipex->error = 'f';
			return (0);
		}
	}
	if (i == argc - 1)
	{
		if (access(argv[i], W_OK))
		{
			pipex->error = 'F';
			return (0);
		}
	}
	return (1);
}

/*
Desc: verify if files and command can be Write, Read and Execute
IN	: argc, argv, envp, array of pipe structure
OUT : 0 or 1
*/

int	fd_verificator_bonus(int argc, char **argv, char **envp, t_pipe *pipex)
{
	int	i;

	i = 0;
	while (++i < argc)
	{
		pipex->op.cmderr = i - pipex->bonus.ishere;
		if (!file_verificator(i, argv, argc, pipex))
			return (0);
		if (i > 1 + pipex->bonus.ishere && i < argc - 1)
		{
			if (!cmd_verificator(ft_subs(argv[i], 0,
						rv_strchr(argv[i], ' ')), pipex, envp))
				return (0);
			if (pipex->bonus.ishere)
				pipex->cmdtab[i - 3] = ft_split(argv[i], ' ');
			else
				pipex->cmdtab[i - 2] = ft_split(argv[i], ' ');
		}
		pipex->op.cmderr += pipex->bonus.ishere;
		if (pipex->error != '0')
			return (0);
	}
	return (1);
}

/*
Desc: Do the parsing of the argumments
IN	: argc, argv, envp, array of pipe structure
OUT : 0 or 1
*/

int	ft_parse_here(int argc, char **argv, char **envp, t_pipe *pipex)
{
	pipex->error = '0';
	pipex->bonus.ishere = ft_strcmp(argv[1], "here_doc");
	if (argc < 5 + pipex->bonus.ishere)
	{
		pipex->error = 'n';
		return (0);
	}
	pipex->cmdtab = (char ***)malloc((argc - 3) * sizeof(char **) + 1);
	pipex->cmdpath = (char **)malloc((argc - 3) * sizeof(char *) + 1);
	if (!fd_verificator_bonus(argc, argv, envp, pipex))
		return (0);
	fullparse_bonus(pipex, argc, argv);
	if (pipex->bonus.ishere)
		pipex->argc--;
	return (1);
}
