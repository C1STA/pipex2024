/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wacista <wacista@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 06:17:24 by wacista           #+#    #+#             */
/*   Updated: 2024/10/26 16:21:39 by wacista          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	init_struct(t_p *p)
{
	p->paths = NULL;
	p->cmd_args = NULL;
	p->cmd_path = NULL;
	p->fd = NULL;
	p->child = NULL;
	p->isheredoc = 0;
	p->start = 0;
	p->nb_cmds = 0;
	p->i = 0;
}

void	close_unused_pipes(t_p *p)
{
	int	j;

	j = 0;
	while (j < p->nb_cmds - 1)
	{
		if (j != p->i)
			close(p->fd[j][1]);
		if (j + 1 != p->i)
			close(p->fd[j][0]);
		j++;
	}
}

void	close_pipes_main(t_p *p)
{
	int	i;

	i = 0;
	while (i < p->nb_cmds - 1)
	{
		close(p->fd[i][0]);
		close(p->fd[i][1]);
		i++;
	}
}

bool	init_pipes(t_p *p, int ac, char **av)
{
	int	i;

	init_struct(p);
	if (isheredoc(p, av))
		return (1);
	p->fd = (int **)malloc(sizeof(int *) * ((ac - 2) - p->start));
	if (!p->fd)
		return (error_pipes(p, av, 0, 1), 1);
	i = 0;
	p->nb_cmds = (ac - 1) - p->start;
	while (i < p->nb_cmds - 1)
	{
		p->fd[i] = (int *)malloc(sizeof(int) * 2);
		if (!p->fd[i])
			return (error_pipes(p, av, i, 2), 1);
		if (pipe(p->fd[i]) == -1)
			return (error_pipes(p, av, i, 3), 1);
		i++;
	}
	return (0);
}
