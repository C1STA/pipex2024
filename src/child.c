/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wacista <wacista@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/27 10:28:13 by wacista           #+#    #+#             */
/*   Updated: 2024/10/27 10:29:42 by wacista          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_basic.h"

static bool	isprintable(char *s)
{
	if (!s)
		return (false);
	while (*s)
	{
		if (ft_isprint(*s++))
			return (true);
	}
	return (false);
}

void	child_one(t_p *p, char **av, char **env)
{
	int	infile;

	close (p->fd[0]);
	infile = open(av[1], O_RDONLY);
	if (infile == -1)
		return (close(p->fd[1]), error_return(p, av[0], av[1], 1));
	dup2(infile, STDIN_FILENO);
	dup2(p->fd[1], STDOUT_FILENO);
	close(p->fd[1]);
	close(infile);
	if (!isprintable(av[2]))
		error_return(p, av[0], av[2], 0);
	get_data(p, av[2], env);
	if (!p->cmd_path)
		error_return(p, av[0], *p->cmd_args, 0);
	if (execve(p->cmd_path, p->cmd_args, env) == -1)
		error_return(p, av[0], *p->cmd_args, 0);
}

void	child_two(t_p *p, char **av, char **env)
{
	int	outfile;

	close(p->fd[1]);
	outfile = open(av[4], O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (outfile == -1)
		return (close(p->fd[0]), error_return(p, av[0], av[4], 1));
	dup2(outfile, STDOUT_FILENO);
	dup2(p->fd[0], STDIN_FILENO);
	close(p->fd[0]);
	close(outfile);
	if (!isprintable(av[3]))
		error_return(p, av[0], av[3], 0);
	get_data(p, av[3], env);
	if (!p->cmd_path)
		error_return(p, av[0], *p->cmd_args, 0);
	if (execve(p->cmd_path, p->cmd_args, env) == -1)
		error_return(p, av[0], *p->cmd_args, 0);
}
