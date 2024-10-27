/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_basic.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wacista <wacista@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 18:53:35 by wacista           #+#    #+#             */
/*   Updated: 2024/10/27 10:29:10 by wacista          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BASIC_H
# define PIPEX_BASIC_H

# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <unistd.h>
# include <string.h>
# include <sys/wait.h>
# include <stdbool.h>
# include <errno.h>
# include "libft.h"

typedef struct s_pipe
{
	char	**paths;
	char	**cmd_args;
	char	*cmd_path;
	int		fd[2];
}	t_p;

void	error_return(t_p *p, char *prog, char *cmd, bool n);
void	get_data(t_p *p, char *av, char **env);
void	free_tab(char **arr);
void	free_pipex(t_p *p);
char	**ft_split_args(char const *s);

int		wait_childs(t_p *p);
void	child_process(t_p *p, int ac, char **av, char **env);

void	error_pipes(t_p *p, char **av, int i, int n);
void	error_heredoc(char **av, int n);
void	error_child(t_p *p, char *prog, char *cmd, int n);
void	error_fork(t_p *p, char **av);

bool	init_forks(t_p *p, int ac, char **av, char **env);
bool	init_pipes(t_p *p, int ac, char **av);
bool	isheredoc(t_p *p, char **av);

void	close_unused_pipes(t_p *p);
void	close_pipes_main(t_p *p);

void	child_one(t_p *p, char **av, char **env);
void	child_two(t_p *p, char **av, char **env);

#endif