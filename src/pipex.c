/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wacista <wacista@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 17:43:07 by wacista           #+#    #+#             */
/*   Updated: 2024/10/15 20:36:30 by wacista          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*join_buffer(char *s1, char *s2)
{
	size_t		i;
	char		*dest;

	if (!s2)
		return (s1);
	dest = (char *)malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!dest)
	{
		if (s1)
			free(s1);
		return (NULL);
	}
	i = 0;
	if (s1)
	{
		while (s1[i])
		{
			dest[i] = s1[i];
			i++;
		}
		free(s1);
	}
	while (*s2)
		dest[i++] = *s2++;
	return (dest[i] = '\0', dest);
}

static void	get_paths(t_p *p, char **env)
{
	char	*path_line;	

	while (*env)
	{
		if (ft_strnstr(*env, "PATH=", 5))
			path_line = ft_substr(*env, 5, ft_strlen(*env));
		env++;
	}
	p->paths = ft_split(path_line, ':');
	free(path_line);
	while (*p->paths)
	{
		*p->paths = join_buffer(*p->paths, "/");
		p->paths++;
	}
}

static bool	check_raw_access(t_p *p, char *av)
{
	char	**cmd;

	cmd = ft_split(av, ' ');
	if (!access(*cmd, F_OK | X_OK))
	{
		p->cmd_path = ft_strdup(*cmd);
		p->cmd_args = ft_split(av, ' ');
		free_tab(cmd);
		return (true);
	}
	free_tab(cmd);
	return (false);
}

static void	check_access(t_p *p)
{
	while (*p->paths)
	{
		p->cmd_path = ft_strjoin(*p->paths, *p->cmd_args);
		if (!access(p->cmd_path, F_OK | X_OK))
			return ;
		free(p->cmd_path);
		p->cmd_path = NULL;
		p->paths++;
	}
}

void	get_data(t_p *p, char *av, char **env)
{
	if (!check_raw_access(p, av))
	{
		get_paths(p, env);
		p->cmd_args = ft_split(av, ' ');
		check_access(p);
	}
}
