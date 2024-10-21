/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lonely.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wacista <wacista@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 06:12:42 by wacista           #+#    #+#             */
/*   Updated: 2024/10/21 06:16:28 by wacista          ###   ########.fr       */
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

static void	init_struct(t_p *p)
{
	p->paths = NULL;
	p->cmd_args = NULL;
	p->cmd_path = NULL;
}

int	lonely_cmd(char **av, char **env)
{
	t_p		*p;

	if (!isprintable(av[1]))
		return (ft_printf("%s: command not found\n", av[1]), 127);
	if (!ft_strcmp("here_doc", av[1]))
		return (ft_printf("pipex: syntax error \
near unexpected token `newline'\n"), 2);
	p = (t_p *)malloc(sizeof(t_p));
	if (!p)
		return (ft_printf("pipex: %s\n", strerror(errno)), 1);
	init_struct(p);
	get_data(p, av[1], env);
	if (!p->cmd_path || execve(p->cmd_path, p->cmd_args, env) == -1)
		error_return(p, av[0], *p->cmd_args, 0);
	return (0);
}

int	lonely_cmd_redir(char **av, char **env)
{
	t_p	*p;
	int	infile;

	p = (t_p *)malloc(sizeof(t_p));
	if (!p)
		return (ft_printf("pipex: %s\n", strerror(errno)), 1);
	init_struct(p);
	infile = open(av[1], O_RDONLY);
	if (infile == -1)
		error_return(p, av[0], av[1], 1);
	dup2(infile, STDIN_FILENO);
	close(infile);
	if (!isprintable(av[2]))
		return (free(p), ft_printf("%s: command not found\n", av[2]), 127);
	get_data(p, av[2], env);
	if (!p->cmd_path || execve(p->cmd_path, p->cmd_args, env) == -1)
		error_return(p, av[0], *p->cmd_args, 0);
	return (0);
}
