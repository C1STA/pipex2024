/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wacista <wacista@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 06:18:03 by wacista           #+#    #+#             */
/*   Updated: 2024/10/25 06:20:31 by wacista          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

bool	init_heredoc(char **av)
{
	int		fd;
	int		reader;
	char	*buffer;
	char	*limiter;

	fd = open("/tmp/.pipex_heredoc", O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd == -1)
		return (error_heredoc(av, 2), 1);
	limiter = ft_strjoin(av[2], "\n");
	while (limiter)
	{
		buffer = get_next_line(STDIN_FILENO);
		if (!buffer)
			return (close(fd), free(limiter), error_heredoc(av, 1), 0);
		if (!ft_strcmp(limiter, buffer))
			return (close(fd), free(limiter), free(buffer), 0);
		reader = write(fd, buffer, ft_strlen(buffer));
		if (reader == -1)
			return (close(fd), free(limiter), \
free(buffer), error_heredoc(av, 3), 1);
		free(buffer);
		buffer = NULL;
	}
	return (close(fd), error_heredoc(av, 4), 1);
}

bool	isheredoc(t_p *p, char **av)
{
	if (!ft_strcmp("here_doc", av[1]))
	{
		if (init_heredoc(av))
			return (free(p), 1);
		p->isheredoc = 1;
		p->start = 3;
	}
	else
	{
		p->isheredoc = 0;
		p->start = 2;
	}
	return (0);
}
