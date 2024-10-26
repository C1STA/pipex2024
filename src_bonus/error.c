/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wacista <wacista@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 20:43:29 by wacista           #+#    #+#             */
/*   Updated: 2024/10/25 06:26:58 by wacista          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	error_return(t_p *p, char *prog, char *cmd, bool n)
{
	char	*tmp;

	if (p->cmd_path || n)
	{
		tmp = ft_substr(prog, 2, ft_strlen(prog));
		ft_printf("%s: %s: %s\n", tmp, cmd, strerror(errno));
		if (tmp)
			free(tmp);
	}
	else
		ft_printf("%s: command not found\n", cmd);
	free_pipe(p);
	if (!n)
		exit(127);
	exit(EXIT_FAILURE);
}

void	error_pipes(t_p *p, char **av, int i, int n)
{
	char	*prog;

	prog = ft_substr(av[0], 2, ft_strlen(av[0]));
	ft_printf("%s: %s\n", prog, strerror(errno));
	if (p->isheredoc)
		if (unlink("/tmp/.pipex_heredoc") == -1)
			ft_printf("%s: unlink: %s\n", prog, strerror(errno));
	if (n == 1)
		return (free(prog), free(p));
	else if (n == 2 || n == 3)
	{
		p->i = 0;
		while (p->i < i)
		{
			if (n == 3)
			{
				close(p->fd[p->i][0]);
				close(p->fd[p->i][1]);
			}
			free(p->fd[p->i++]);
		}
		if (n == 3)
			free(p->fd[p->i]);
		return (free(prog), free(p->fd), free(p));
	}
}

void	error_heredoc(char **av, int n)
{
	char	*prog;

	prog = ft_substr(av[0], 2, ft_strlen(av[0]));
	if (!prog)
		prog = "pipex";
	if (n == 1)
	{
		ft_printf("%s: warning: here-document not \
delimited by end-of-file (wanted `%s')\n", prog, av[2]);
		return (free(prog));
	}
	if (n == 2)
	{
		ft_printf("%s: %s: %s\n", prog, "/tmp/.pipex_heredoc", strerror(errno));
		return (free(prog));
	}
	if (n == 3)
	{
		ft_printf("%s: write: %s\n", prog, strerror(errno));
		if (unlink("/tmp/.pipex_heredoc") == -1)
			ft_printf("%s: unlink: %s\n", prog, strerror(errno));
		return (free(prog));
	}
	if (n == 4)
		return (ft_printf("%s: %s\n", prog, strerror(errno)), free(prog));
}

void	error_child(t_p *p, char *prog, char *cmd, int n)
{
	prog = ft_substr(prog, 2, ft_strlen(prog));
	if (!prog)
		prog = "pipex";
	if (p->i != p->nb_cmds - 1)
	{
		close(p->fd[p->i][1]);
		close(STDOUT_FILENO);
	}
	if (p->i != 0)
	{
		//close(p->fd[p->i - 1][0]);
		close(STDIN_FILENO);
	}
	if (p->cmd_path || n)
		ft_printf("%s: %s: %s\n", prog, cmd, strerror(errno));
	else
		ft_printf("%s: command not found\n", cmd);
	free_pipe(p);
	free(prog);
	close(STDIN_FILENO);
	close(STDOUT_FILENO);
	if (!n)
		exit(127);
	exit(EXIT_FAILURE);
}

void	error_fork(t_p *p, char **av)
{
	int		j;
	char	*prog;

	prog = ft_substr(av[0], 2, ft_strlen(av[0]));
	if (!prog)
		prog = "pipex";
	ft_printf("%s: %s\n", prog, strerror(errno));
	if (p->isheredoc)
		if (unlink("/tmp/.pipex_heredoc") == -1)
			ft_printf("%s: unlink: %s\n", prog, strerror(errno));
	j = 0;
	while (j < p->nb_cmds - 1)
	{
		close(p->fd[j][0]);
		close(p->fd[j][1]);
		free(p->fd[j++]);
	}
	if (p->child)
		free(p->child);
	return (free(prog), free(p->fd), free(p));
}
