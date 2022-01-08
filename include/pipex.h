/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jforner <jforner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/02 12:18:26 by jforner           #+#    #+#             */
/*   Updated: 2022/01/05 14:52:09 by jforner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <fcntl.h>
# include <errno.h>
# include <string.h>
# include <sys/types.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

typedef struct s_bonus
{
	char	*heredoc;
	int		ishere;
}				t_bonus;

typedef struct s_open
{
	int		filein;
	int		fileout;
	int		cmderr;
}				t_open;

typedef struct s_pipe {
	char	error;
	char	***cmdtab;
	char	*flpath[3];
	int		argc;
	char	**cmdpath;
	int		pip[2];
	t_bonus	bonus;
	t_open	op;
}				t_pipe;

//parse
int		ft_parse(int argc, char **argv, char **envp, t_pipe *pipex);
int		fd_verificator(int argc, char **argv, char **envp, t_pipe *pipex);
int		cmd_verificator(char *argv, t_pipe *pipex, char **envp);
int		cmd_verificator2(char *argv, t_pipe *pipex, char **path);
void	fullparse(t_pipe *pipex, int argc, char **argv);

//parse util
void	create_temp(t_pipe *pipex);

//cat utils
char	*ft_fullstr(char *s, unsigned int start, size_t len, char *str);
char	*ft_substr(char *s, unsigned int start, size_t len);
void	*ft_memset(void *str, char c, size_t n);

//cat
char	*ft_strjoin(char *s1, char *s2);
size_t	ft_strlen(char *str);
int		ft_buftoline(char *buf, int fd, char **line);
char	*ft_cat(int fd);

//core
int		pipeline(int ncmds, int output[2], t_pipe *pipex);
int		core_pipex(int ncmds, t_pipe *pipex);
int		core_pipex(int ncmds, t_pipe *pipex);
int		checkfork(pid_t	*pid, t_pipe *pipex);

//error
int		ft_puterror(char **array, t_pipe *pipex);

//utils
void	ft_putchar_fd(char c, int fd);
void	ft_putstr_fd(char *s, int fd);
char	*sjoin(char *s1, char *s2);
void	*ft_calloc(size_t nmemb, size_t size);
char	*str_next_str(char *str, char *search);

//utils2
int		ft_sstr(char *str, char *search);
int		ft_0sstr(char *str, char *search);
int		rv_strchr(char	*str, char ch);
char	*ft_subs(char *s, unsigned int start, size_t len);
int		tab_len(char **tab);

//split
void	ft_malloc_error(char **tab, int size);
int		ft_splitage(char *s, char c, char **tab, unsigned int nb_word);
int		ft_tablen(char *str, char sep, char ***tab,
			unsigned int *nb_word);
char	**ft_split(char *s, char c);

//complete
char	**ft_tabdup(char **tab);
void	jointab(t_pipe *pipex, int itab, int min, int *max);
int		ft_countchr(char *str, char ch);
void	mkarg(t_pipe *pipex);

// void	banana();

#endif
