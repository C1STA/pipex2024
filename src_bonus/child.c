/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wacista <wacista@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 06:15:59 by wacista           #+#    #+#             */
/*   Updated: 2024/10/26 10:30:00 by wacista          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

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

int	wait_childs(t_p *p)
{
	int	i;
	int	status;

	i = 0;
	status = 0;
	while (i < p->nb_cmds)
	{
		waitpid(p->child[i], &status, 0);
		if (WIFEXITED(status))
			status = (WEXITSTATUS(status));
		else if (WIFSIGNALED(status))
			status = 128 + WTERMSIG(status);
		i++;
	}
	return (status);
}

void	child_process(t_p *p, int ac, char **av, char **env)
{
	int	infile;
	int	outfile;

	printf("je suis: %d: %d\n", p->i, getpid());
	close_unused_pipes(p);
	if (p->i != 0)
		dup2(p->fd[p->i - 1][0], STDIN_FILENO);
		//close(p->fd[p->i - 1][0]);
	else
	{
		if (p->isheredoc == 1)
			infile = open("/tmp/.pipex_heredoc", O_RDONLY);
		else
			infile = open(av[1], O_RDONLY);
		if (infile == -1)
			error_child(p, av[0], av[1], 1);
		dup2(infile, STDIN_FILENO);
		close(infile);
		//close(p->fd[p->i][0]);
	}
	if (p->i != p->nb_cmds - 1)
		dup2(p->fd[p->i][1], STDOUT_FILENO);
		//close(p->fd[p->i][1]);
	else
	{
		if (p->isheredoc == 1)
			outfile = open(av[ac - 1], O_CREAT | O_WRONLY | O_APPEND, 0644);
		else
			outfile = open(av[ac - 1], O_CREAT | O_WRONLY | O_TRUNC, 0644);
		if (outfile == -1)
			error_child(p, av[0], av[ac - 1], 1);
		dup2(outfile, STDOUT_FILENO);
		close(outfile);
	}
	if (!isprintable(av[p->i + p->start]))
		return (error_child(p, av[0], av[p->i + p->start], 0));
	get_data(p, av[p->i + p->start], env);
	if (!p->cmd_path || execve(p->cmd_path, p->cmd_args, env) == -1)
		error_child(p, av[0], av[p->i + p->start], 0);
}
