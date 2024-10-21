/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wacista <wacista@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 01:11:21 by wacista           #+#    #+#             */
/*   Updated: 2024/10/21 09:23:25 by wacista          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	init_st(t_p *p)
{
	p->paths = NULL;
	p->cmd_args = NULL;
	p->cmd_path = NULL;
	p->isheredoc = 0;
	p->start = 0;
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
}

int	init_heredoc(char **av)
{
	int		fd;
	int		reader;
	char	*buffer;
	char	*limiter;

	fd = open("/tmp/.pipex_heredoc", O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd == -1)
		return (error_heredoc(av, 2), 1);
	limiter = ft_strjoin(av[2], "\n");
	while (1)
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
	return (0);
}

void	init_pipes(int ac, char **av, char **env)
{
	t_p *p;

	p = (t_p *)malloc(sizeof(t_p));
	if (!p)
		return ;
	if (!ft_strcmp("here_doc", av[1]))
	{
		init_heredoc(av);
		p->isheredoc = 1;
		p->start = 3;
	}
	else
	{
		p->isheredoc = 0;
		p->start = 2;
	}
	while (p->start < ac - 1)
	{
		printf("%s\n", av[p->start]);
		p->start++;
	}
	free(p);
}

int	main(int ac, char **av, char **env)
{
	if (ac < 2)
		return (ft_printf("pipex: not enough arguments"), 2);
	if (ac == 2)
		return (lonely_cmd(av, env));
	if (ac == 3)
		return (lonely_cmd_redir(av, env));
	if (ac > 4)
		init_pipes(ac, av, env);
	return (0);
}
