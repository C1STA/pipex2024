#include "pipex.h"

void	child_one(t_p *p, char **av, char **env)
{
	int	infile;

	close (p->fd[0]);
	if (!access(av[1], R_OK))
	{
		infile = open(av[1], O_RDONLY);
		if (infile == -1)
			return (close(p->fd[1]), error_return (p, av[1]));
	}
	else
		return (close(p->fd[1]), error_return (p, av[1]));
	dup2(infile, STDIN_FILENO);
	dup2(p->fd[1], STDOUT_FILENO);
	close(p->fd[1]);
	close(infile);
	get_data(p, av[2], env);
	if (!p->cmd_path)
		error_return(p, *p->cmd_args);
	if (execve(p->cmd_path, p->cmd_args, env) == -1)
		error_return(p, *p->cmd_args);
}

void	child_two(t_p *p, char **av, char **env)
{
	int	outfile;

	close(p->fd[1]);
	outfile = open(av[4], O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (outfile == -1 || access(av[4], W_OK) == -1)
	{
		if (!outfile)
			close(outfile);
		return (close(p->fd[0]), error_return(p, av[4]));
	}
	dup2(p->fd[0], STDIN_FILENO);
	dup2(outfile, STDOUT_FILENO);
	close(p->fd[0]);
	close(outfile);
	get_data(p, av[3], env);
	if (!p->cmd_path)
		error_return(p, *p->cmd_args);
	if (execve(p->cmd_path, p->cmd_args, env) == -1)
		error_return(p, *p->cmd_args);
}

void	pipex(t_p *p, char **av, char **env)
{
	int		status;
	pid_t	child1;
	pid_t	child2;

	if (pipe(p->fd) == -1)
		return (perror("pipe"));
	child1 = fork();
	if (child1 == -1)
		return (perror("fork"));
	if (!child1)
		child_one(p, av, env);
	child2 = fork();
	if (child2 == -1)
		return (perror("fork"));
	if (!child2)
		child_two(p, av, env);
	close(p->fd[0]);
	close(p->fd[1]);
	waitpid(child1, &status, 0);
	waitpid(child2, &status, 0);
}

int	main(int ac, char **av, char **env)
{
	t_p	*p;

	if (ac != 5)
		return(ft_putstr_fd("pipex: four arguments required\n", 2), EXIT_FAILURE);
	p = (t_p *)malloc(sizeof(t_p));
	if (!p)
		return (ft_putstr_fd("pipex: fatal error: malloc fail\n", 2), EXIT_FAILURE);
	pipex(p, av, env);
	return (EXIT_SUCCESS);
}
