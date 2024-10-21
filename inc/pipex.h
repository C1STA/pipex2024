/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wacista <wacista@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 18:53:35 by wacista           #+#    #+#             */
/*   Updated: 2024/10/21 09:08:54 by wacista          ###   ########.fr       */
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
	bool	isheredoc;
	int		start;
}	t_p;

void	error_return(t_p *p, char *prog, char *cmd, bool n);
void	get_data(t_p *p, char *av, char **env);
void	free_tab(char **arr);
void	free_pipex(t_p *p);
char	**ft_split_args(char const *s);
int		lonely_cmd_redir(char **av, char **env);
int		lonely_cmd(char **av, char **env);

#endif