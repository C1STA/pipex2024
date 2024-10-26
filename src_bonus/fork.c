/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wacista <wacista@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 06:14:51 by wacista           #+#    #+#             */
/*   Updated: 2024/10/25 06:21:19 by wacista          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

bool	init_forks(t_p *p, int ac, char **av, char **env)
{
	p->i = 0;
	p->child = (pid_t *)malloc(sizeof(pid_t) * p->nb_cmds);
	if (!p->child)
		return (error_fork(p, av), 1);
	while (p->i < p->nb_cmds)
	{
		p->child[p->i] = fork();
		if (p->child[p->i] == -1)
			return (error_fork(p, av), 1);
		if (!p->child[p->i])
			child_process(p, ac, av, env);
		p->i++;
	}
	return (0);
}
