/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wacista <wacista@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 01:11:21 by wacista           #+#    #+#             */
/*   Updated: 2024/10/26 16:27:06 by wacista          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int ac, char **av, char **env)
{
	t_p	*p;
	int	status;

	if (ac < 5)
		return (ft_printf("pipex: accepts 4+ args, received %d\n", ac - 1), 2);
	status = 0;
	if (ac > 4)
	{
		p = (t_p *)malloc(sizeof(t_p));
		if (!p)
			return (ft_printf("pipex: %s\n", strerror(errno)), 1);
		if (init_pipes(p, ac, av))
			return (1);
		if (init_forks(p, ac, av, env))
			return (1);
		close_pipes_main(p);
		status = (wait_childs(p));
		free_pipe(p);
	}
	return (status);
}
