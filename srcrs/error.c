/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jforner <jforner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/02 12:22:16 by jforner           #+#    #+#             */
/*   Updated: 2021/12/20 16:18:12 by jforner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

/*
Desc: print error
IN	: argv, array of pipe structure
OUT	: 0
*/
int	ft_puterror(char **array, t_pipe *pipex)
{
	char	*strerr;

	ft_putstr_fd("Error\n", 2);
	if (pipex->error == 'O' || pipex->error == 'F' || pipex->error == 'f')
	{
		strerr = sjoin(array[pipex->op.cmderr], "\t: ");
		ft_putstr_fd(strerr, 2);
		free(strerr);
		ft_putstr_fd(strerror(errno), 2);
	}
	if (pipex->error == '0')
		ft_putstr_fd(strerror(errno), 2);
	if (pipex->error == 'h')
		ft_putstr_fd("Failed to fork", 2);
	if (pipex->error == 'p')
		ft_putstr_fd("Failed to pipe", 2);
	if (pipex->error == 'n')
		ft_putstr_fd("The number of argumments is not valid", 2);
	return (0);
}
