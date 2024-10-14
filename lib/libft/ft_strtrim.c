/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wacista <wacista@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 15:58:55 by wacista           #+#    #+#             */
/*   Updated: 2024/05/30 21:32:50 by wacista          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	is_trimmable(char c, char const *set)
{
	while (*set)
	{
		if (*set++ == c)
			return (1);
	}
	return (0);
}

static int	full_len(char const *s1, char const *set)
{
	int	i;
	int	len;

	i = 0;
	while (s1[i] && is_trimmable(s1[i], set))
		i++;
	len = ft_strlen(s1) - i;
	i = ft_strlen(s1) - 1;
	while (s1[i] && is_trimmable(s1[i], set))
		i--;
	len -= (ft_strlen(s1) - i) - 1;
	return (len);
}

static char	*get_trim(char const *s1, char const *set, char *dest)
{
	int	i;
	int	j;
	int	save;

	i = 0;
	while (s1[i] && is_trimmable(s1[i], set))
		i++;
	j = 0;
	save = ft_strlen(s1) - 1;
	while (s1[save] && is_trimmable(s1[save], set))
		save--;
	while ((i + j) <= save)
	{
		dest[j] = s1[i + j];
		j++;
	}
	dest[j] = '\0';
	return (dest);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	int		len;
	char	*dest;

	if (!s1 || !set)
		return (NULL);
	len = full_len(s1, set);
	if (len < 0)
		return (ft_strdup(""));
	dest = (char *)malloc(sizeof(char) * len + 1);
	if (!dest)
		return (NULL);
	dest = get_trim(s1, set, dest);
	return (dest);
}
