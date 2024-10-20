/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wacista <wacista@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 22:25:47 by wacista           #+#    #+#             */
/*   Updated: 2024/10/20 03:48:49 by wacista          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	child_one(t_p *p, char **av, char **env)
{
	int	infile;

	close (p->fd[0]);
	infile = open(av[1], O_RDONLY);
	if (infile == -1)
		return (close(p->fd[1]), error_return (p, av[0], av[1], 1));
	dup2(infile, STDIN_FILENO);
	dup2(p->fd[1], STDOUT_FILENO);
	close(p->fd[1]);
	close(infile);
	get_data(p, av[2], env);
	if (!p->cmd_path)
		error_return(p, av[0], *p->cmd_args, 0);
	if (execve(p->cmd_path, p->cmd_args, env) == -1)
		error_return(p, av[0], *p->cmd_args, 0);
}

static void	child_two(t_p *p, char **av, char **env)
{
	int	outfile;

	close(p->fd[1]);
	outfile = open(av[4], O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (outfile == -1)
		return (close(p->fd[0]), error_return(p, av[0], av[4], 1));
	dup2(outfile, STDOUT_FILENO);
	dup2(p->fd[0], STDIN_FILENO);
	close(p->fd[0]);
	close(outfile);
	get_data(p, av[3], env);
	if (!p->cmd_path)
		error_return(p, av[0], *p->cmd_args, 0);
	if (execve(p->cmd_path, p->cmd_args, env) == -1)
		error_return(p, av[0], *p->cmd_args, 0);
}

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
		return (ft_printf("pipex: four arguments required\n"), 2);
	p = (t_p *)malloc(sizeof(t_p));
	if (!p)
		return (ft_printf("pipex: %s\n", strerror(errno)), 1);
	init_struct(p);
	status = pipex(p, av, env);
	free_pipex(p);
	return (status);
}
