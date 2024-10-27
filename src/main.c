/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wacista <wacista@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 22:25:47 by wacista           #+#    #+#             */
/*   Updated: 2024/10/27 10:28:34 by wacista          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_basic.h"

static int	pipex(t_p *p, char **av, char **env)
{
	int		status;
	pid_t	child1;
	pid_t	child2;

	if (pipe(p->fd) == -1)
		return (perror("pipe"), 1);
	child1 = fork();
	if (child1 == -1)
		return (close(p->fd[0]), close(p->fd[1]), perror("fork"), 1);
	if (!child1)
		child_one(p, av, env);
	child2 = fork();
	if (child2 == -1)
		return (close(p->fd[0]), close(p->fd[1]), perror("fork"), 1);
	if (!child2)
		child_two(p, av, env);
	close(p->fd[0]);
	close(p->fd[1]);
	waitpid(child1, NULL, 0);
	waitpid(child2, &status, 0);
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	return (0);
}

static void	init_struct(t_p *p)
{
	p->paths = NULL;
	p->cmd_args = NULL;
	p->cmd_path = NULL;
}

int	main(int ac, char **av, char **env)
{
	t_p	*p;
	int	status;

	if (ac != 5)
		return (ft_printf("pipex: accepts 4 args, received %d\n", ac - 1), 2);
	p = (t_p *)malloc(sizeof(t_p));
	if (!p)
		return (ft_printf("pipex: %s\n", strerror(errno)), 1);
	init_struct(p);
	status = pipex(p, av, env);
	free_pipex(p);
	return (status);
}
