/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wacista <wacista@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 10:38:41 by wacista           #+#    #+#             */
/*   Updated: 2024/10/21 07:32:20 by wacista          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

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

int	is_newline(char *s)
{
	unsigned int	i;

	if (!s)
		return (0);
	i = 0;
	while (s[i])
	{
		if (s[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}

char	*cpy_newline(char *s)
{
	int		i;
	char	*dest;

	if (!s)
		return (NULL);
	i = 0;
	while (s[i] && s[i] != '\n')
		i++;
	if (s[i] == '\n')
		i++;
	dest = (char *)malloc(sizeof(char) * (i + 1));
	if (!dest)
		return (free_buffer(s), NULL);
	i = 0;
	while (s[i] && s[i] != '\n')
	{
		dest[i] = s[i];
		i++;
	}
	if (s[i] == '\n')
		dest[i++] = '\n';
	dest[i] = '\0';
	return (dest);
}

char	*new_buffer(char *s)
{
	int		i;
	int		j;
	char	*dest;

	if (!s)
		return (NULL);
	i = 0;
	while (s[i] && s[i] != '\n')
		i++;
	if (!s[i])
		return (free(s), NULL);
	dest = (char *)malloc(sizeof(char) * (ft_strlen(s) - i));
	if (!dest)
		return (free(s), NULL);
	j = 0;
	if (s[i] == '\n')
		i++;
	while (s[i])
		dest[j++] = s[i++];
	dest[j] = '\0';
	if (!*dest)
		return (free(dest), free(s), NULL);
	return (free(s), dest);
}
