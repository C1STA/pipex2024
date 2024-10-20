/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wacista <wacista@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 18:42:48 by wacista           #+#    #+#             */
/*   Updated: 2024/10/19 21:16:44 by wacista          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

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

static char	**fill_words(char **dest, char const *s, char c)
{
	int	i;
	int	j;
	int	k;

	i = 0;
	k = 0;
	while (s[i])
	{
		while (s[i] && s[i] == c)
			i++;
		j = i;
		while (s[i] && s[i] != c)
			i++;
		if (i > j)
		{
			dest[k] = (char *)malloc(sizeof(char) * ((i - j) + 1));
			if (!dest[k])
				return (ft_free(dest, k), NULL);
			ft_strncpy(dest[k++], &s[j], i - j);
		}
	}
	dest[k] = NULL;
	return (dest);
}

char	**ft_split(char const *s, char c)
{
	int		i;
	int		w;
	char	**dest;

	i = 0;
	w = 0;
	if (!s)
		return (NULL);
	while (s[i])
	{
		while (s[i] && s[i] == c)
			i++;
		if (s[i])
			w++;
		while (s[i] && s[i] != c)
			i++;
	}
	dest = (char **)malloc(sizeof(char *) * (w + 1));
	if (!dest)
		return (NULL);
	return (fill_words(dest, s, c));
}
