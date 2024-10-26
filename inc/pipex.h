/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wacista <wacista@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 18:53:35 by wacista           #+#    #+#             */
/*   Updated: 2024/10/25 06:26:35 by wacista          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <unistd.h>
# include <string.h>
# include <sys/wait.h>
# include <stdbool.h>
# include <errno.h>
# include "libft.h"

typedef struct s_pipex
{
	char	**paths;
	char	**cmd_args;
	char	*cmd_path;
	int		**fd;
	pid_t	*child;
	bool	isheredoc;
	int		start;
	int		nb_cmds;
	int		i;
}	t_p;

void	error_return(t_p *p, char *prog, char *cmd, bool n);
void	get_data(t_p *p, char *av, char **env);
void	free_tab(char **arr);
void	free_pipe(t_p *p);
char	**ft_split_args(char const *s);
int		lonely_cmd_redir(char **av, char **env);
int		lonely_cmd(char **av, char **env);

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

#endif