/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wacista <wacista@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 17:43:07 by wacista           #+#    #+#             */
/*   Updated: 2024/10/21 07:03:46 by wacista          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	get_paths(t_p *p, char **env)
{
	int		i;
	char	*path_line;

	path_line = NULL;
	while (*env)
	{
		if (ft_strnstr(*env, "PATH=", 5))
			path_line = ft_substr(*env, 5, ft_strlen(*env));
		env++;
	}
	if (!path_line)
		return ;
	p->paths = ft_split(path_line, ':');
	free(path_line);
	i = 0;
	while (p->paths[i])
	{
		p->paths[i] = join_buffer(p->paths[i], "/");
		i++;
	}
}

static bool	check_raw_access(t_p *p, char *av)
{
	char	**cmd;

	cmd = ft_split_args(av);
	if (!access(*cmd, F_OK | X_OK))
	{
		p->cmd_path = ft_strdup(*cmd);
		p->cmd_args = ft_split_args(av);
		free_tab(cmd);
		return (true);
	}
	free_tab(cmd);
	return (false);
}

static void	check_access(t_p *p)
{
	int	i;

	i = 0;
	if (!p->paths)
		return ;
	while (p->paths[i])
	{
		p->cmd_path = ft_strjoin(p->paths[i], *p->cmd_args);
		if (!access(p->cmd_path, F_OK | X_OK))
			return ;
		free(p->cmd_path);
		p->cmd_path = NULL;
		i++;
	}
}

void	get_data(t_p *p, char *av, char **env)
{
	if (!check_raw_access(p, av))
	{
		get_paths(p, env);
		p->cmd_args = ft_split_args(av);
		check_access(p);
	}
}
