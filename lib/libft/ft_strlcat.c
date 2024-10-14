/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wacista <wacista@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 16:22:42 by wacista           #+#    #+#             */
/*   Updated: 2024/05/29 17:12:50 by wacista          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t siz)
{
	size_t	len_dst;
	size_t	len_src;
	size_t	buffer;
	size_t	i;
	size_t	j;

	len_src = ft_strlen(src);
	if (!siz)
		return (len_src);
	len_dst = ft_strlen(dst);
	if (!*src && siz > len_dst)
		return (len_dst);
	if (siz <= len_dst || !*src)
		return (siz + len_src);
	buffer = siz - len_dst;
	i = 0;
	j = len_dst;
	while (src[i] && i < buffer - 1)
	{
		dst[j] = src[i];
		i++;
		j++;
	}
	dst[j] = '\0';
	return (len_dst + len_src);
}
