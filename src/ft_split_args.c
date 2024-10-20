/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_args.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wacista <wacista@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 18:42:48 by wacista           #+#    #+#             */
/*   Updated: 2024/10/20 02:54:20 by wacista          ###   ########.fr       */
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

static char	*alloc_word(char const **s, char quote)
{
	char		*word;
	char const	*start;

	start = *s;
	while (**s && (quote || (**s != ' ' && **s != '\'' && **s != '"')))
	{
		if (**s == quote)
			break ;
		(*s)++;
	}
	word = (char *)malloc(*s - start + 1);
	if (!word)
		return (NULL);
	ft_strncpy(word, start, (*s - start));
	if (quote && **s == quote)
		(*s)++;
	return (word);
}

static char	**fill_words(char **dest, char const *s)
{
	int		i;
	char	quote;

	i = 0;
	while (*s)
	{
		quote = 0;
		while (*s && ((*s >= 9 && *s <= 13) || *s == 32))
			s++;
		if (!*s)
			break ;
		if (*s == '\'' || *s == '"')
			quote = *s++;
		dest[i] = alloc_word(&s, quote);
		if (!dest[i])
			return (ft_free(dest, i), NULL);
		i++;
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

char	**ft_split_args(char const *s)
{
	char	**dest;

	if (!s)
		return (NULL);
	dest = (char **)malloc(sizeof(char *) * (count_words(s) + 1));
	if (!dest)
		return (NULL);
	return (fill_words(dest, s));
}
