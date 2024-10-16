/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wacista <wacista@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 20:43:29 by wacista           #+#    #+#             */
/*   Updated: 2024/10/16 23:13:16 by wacista          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	error_return(t_p *p, char *s, bool n)
{
	ft_putstr_fd(s, 2);
	ft_putstr_fd(": ", 2);
	if (p->cmd_path || n)
		perror("");
	else
	{
		ft_putstr_fd("command not found\n", 2);
		free_pipex(p);
		exit(127);
	}
	free_pipex(p);
	exit(EXIT_FAILURE);
}
