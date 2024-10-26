/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wacista <wacista@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 14:25:52 by wacista           #+#    #+#             */
/*   Updated: 2024/10/25 06:19:34 by wacista          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	free_tab(char **arr)
{
	int	i;

	i = 0;
	if (!arr)
		return ;
	while (arr[i])
		free(arr[i++]);
	free(arr);
}

void	free_pipe(t_p *p)
{
	int	i;

	i = 0;
	free_tab(p->paths);
	free_tab(p->cmd_args);
	if (p->cmd_path)
		free(p->cmd_path);
	if (p->fd)
	{
		while (i < p->nb_cmds - 1)
		{
			if (p->fd[i] != NULL)
				free(p->fd[i++]);
			else
				break ;
		}
		free(p->fd);
	}
	if (p->child != NULL)
		free(p->child);
	free(p);
}
