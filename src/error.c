/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wacista <wacista@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 20:43:29 by wacista           #+#    #+#             */
/*   Updated: 2024/10/26 17:47:37 by wacista          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_basic.h"

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
	free_pipex(p);
	if (!n)
		exit(127);
	exit(EXIT_FAILURE);
}
