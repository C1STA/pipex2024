/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wacista <wacista@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 10:36:14 by wacista           #+#    #+#             */
/*   Updated: 2024/06/11 18:14:26 by wacista          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	free_buffer(char *buffer)
{
	if (buffer)
	{
		free(buffer);
		buffer = NULL;
	}
}

static char	*read_buffer(int fd, char *buffer)
{
	int		n;
	char	*tmp;

	tmp = (char *)malloc(sizeof(char) * BUFFER_SIZE + 1);
	if (!tmp)
		return (free_buffer(buffer), NULL);
	n = 1;
	while (n && !is_newline(buffer))
	{
		n = read(fd, tmp, BUFFER_SIZE);
		if (n == -1)
			return (free(tmp), free_buffer(buffer), NULL);
		if (!buffer && !n)
			return (free(tmp), NULL);
		tmp[n] = '\0';
		buffer = join_buffer(buffer, tmp);
		if (!buffer)
			return (free(tmp), NULL);
	}
	return (free(tmp), buffer);
}

char	*get_next_line(int fd)
{
	char		*line;
	static char	*buffer;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (free_buffer(buffer), NULL);
	buffer = read_buffer(fd, buffer);
	if (!buffer)
		return (NULL);
	line = cpy_newline(buffer);
	if (!line)
	{
		buffer = NULL;
		return (NULL);
	}
	buffer = new_buffer(buffer);
	return (line);
}
