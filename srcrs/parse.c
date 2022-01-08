/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jforner <jforner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/02 19:00:56 by jforner           #+#    #+#             */
/*   Updated: 2022/01/06 12:24:43 by jforner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

void	fullparse(t_pipe *pipex, int argc, char **argv)
{
	int	i;

	i = -1;
	while (++i < argc - 3)
	{
		free(pipex->cmdtab[i][0]);
		pipex->cmdtab[i][0] = ft_subs(pipex->cmdpath[i], 0,
				ft_strlen(pipex->cmdpath[i]));
	}
	pipex->argc = argc;
	pipex->flpath[0] = ft_subs(argv[1], 0, ft_strlen(argv[1]));
	pipex->flpath[1] = ft_subs(argv[argc - 1], 0, ft_strlen(argv[argc - 1]));
	create_temp(pipex);
	pipex->op.fileout = open(pipex->flpath[1], O_WRONLY | O_TRUNC);
}

/*
Desc: Check if a command can be executed with one path from $PATH part 1
IN	: argv, array of pipe structure, place of the actual command,
paths for the commands
OUT : 0 or 1
*/

int	cmd_verificator2(char *argv, t_pipe *pipex, char **path)
{
	int		j;
	char	*str;

	j = -1;
	while (path[++j] != NULL)
	{
		str = ft_strjoin(sjoin(path[j], "/"), argv);
		if (access(str, X_OK) == 0)
			pipex->cmdpath[pipex->op.cmderr - 2]
				= ft_subs(str, 0, ft_strlen(str));
		free (str);
	}
	ft_malloc_error(path, j);
	free(argv);
	if (pipex->cmdpath[pipex->op.cmderr - 2] != NULL)
	{
		errno = 0;
		return (1);
	}
	pipex->error = 'O';
	return (0);
}
/*
Desc: Check if a command can be executed with one path from $PATH part 1
IN	: argv, array of pipe structure, place of the actual command, envp
OUT : 0 or 1
*/

int	cmd_verificator(char *argv, t_pipe *pipex, char **envp)
{
	char	**path;
	char	*str;
	int		j;

	pipex->cmdpath[pipex->op.cmderr - 2] = NULL;
	str = sjoin("./", argv);
	if (access(str, X_OK) == 0)
		pipex->cmdpath[pipex->op.cmderr - 2]
			= ft_subs(str, 0, ft_strlen(str));
	j = -1;
	while (envp[++j] != NULL)
	{
		if (ft_0sstr(envp[j], "PATH="))
		{
			free(str);
			str = ft_subs(envp[j], 5, ft_strlen(envp[j]));
		}
	}
	path = ft_split(str, ':');
	free (str);
	return (cmd_verificator2(argv, pipex, path));
}
/*
Desc: verify if files and command can be Write, Read and Execute
IN	: argc, argv, envp, array of pipe structure
OUT : 0 or 1
*/

int	fd_verificator(int argc, char **argv, char **envp, t_pipe *pipex)
{
	int	i;

	i = 0;
	while (++i < argc)
	{
		pipex->op.cmderr = i;
		if (i == 1)
			if (access(argv[i], R_OK) == -1)
				pipex->error = 'f';
		if (i == argc - 1)
			if (access(argv[i], W_OK) == -1)
				pipex->error = 'F';
		if (i != 1 && i != argc - 1)
		{
			if (!cmd_verificator(ft_subs(argv[i], 0,
						rv_strchr(argv[i], ' ')), pipex, envp))
				return (0);
			pipex->cmdtab[i - 2] = ft_split(argv[i], ' ');
		}
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

int	ft_parse(int argc, char **argv, char **envp, t_pipe *pipex)
{
	pipex->error = '0';
	if (argc != 5)
	{
		pipex->error = 'n';
		return (0);
	}
	pipex->cmdtab = (char ***)malloc((argc - 3) * sizeof(char **) + 1);
	pipex->cmdpath = (char **)malloc((argc - 3) * sizeof(char *) + 1);
	if (!fd_verificator(argc, argv, envp, pipex))
		return (0);
	fullparse(pipex, argc, argv);
	return (1);
}
