/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jforner <jforner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/02 12:18:26 by jforner           #+#    #+#             */
/*   Updated: 2021/12/20 21:43:54 by jforner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

# include "../include/pipex.h"

//bonus
	// utils
int		ft_strcmp(const char *s1, const char *s2);
char	*reanding0(t_pipe *pipex);
void	heredoc(t_pipe *pipex);
	//parse
int		ft_parse_here(int argc, char **argv, char **envp, t_pipe *pipex);
int		fd_verificator_bonus(int argc, char **argv, char **envp, t_pipe *pipex);
int		file_verificator(int i, char **argv, int argc, t_pipe *pipex);
void	fullparse_bonus(t_pipe *pipex, int argc, char **argv);

#endif
