/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_split.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wacista <wacista@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 18:42:48 by wacista           #+#    #+#             */
/*   Updated: 2024/10/18 22:56:29 by wacista          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	ft_free(char **dest, int k)
{
	int	i;

	i = 0;
	while (i < k)
	{
		free(dest[i]);
		dest[i] = NULL;
		i++;
	}
	free(dest);
	dest = NULL;
}

static char	*ft_strncpy(char *dest, char const *src, int size)
{
	int	i;

	i = 0;
	while (src[i] && i < size)
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

static char	**fill_words(char **dest, char const *s)
{
	int		i;
	char	*start;
	char	quote;

	i = 0;
	while (*s)
	{
		while (*s && ((*s >= 9 && *s <= 13) || *s == 32))
			s++;
		if (!*s)
			break ;
		start = (char *)s;
		quote = 0;
		if (*s == '\'' || *s == '"')
		{
			quote = *s++;
			start++;
			while (*s && *s != quote)
				s++;
			if (*s)
				s++;
		}
		else
		{
			while (*s && (*s != ' ' && *s != '\'' && *s != '"'))
				s++;
		}
		if (s > start)
		{
			dest[i] = (char *)malloc(sizeof(char) * (s - start + 1));
			if (!dest[i])
				return (ft_free(dest, i), NULL);
			if (quote)
				quote = 1;
			ft_strncpy(dest[i++], start, s - start - quote);
		}
	}
	dest[i] = NULL;
	return (dest);
}

static int	count_words(char const *s)
{
	int		words;
	char	quote;

	words = 0;
	while (*s)
	{
		while (*s && ((*s >= 9 && *s <= 13) || *s == 32))
			s++;
		if (*s)
			words++;
		else
			break ;
		if (*s == '\'' || *s == '"')
		{
			quote = *s++;
			while (*s && *s != quote)
				s++;
			if (*s)
				s++;
		}
		else
			while (*s && (*s != ' ' && *s != '\'' && *s != '"'))
				s++;
	}
	return (words);
}

char	**new_split(char const *s)
{
	char	**dest;

	if (!s)
		return (NULL);
	dest = (char **)malloc(sizeof(char *) * (count_words(s) + 1));
	if (!dest)
		return (NULL);
	return (fill_words(dest, s));
}
