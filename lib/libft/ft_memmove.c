/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wacista <wacista@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 14:58:01 by wacista           #+#    #+#             */
/*   Updated: 2024/05/29 16:56:23 by wacista          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	size_t			i;
	unsigned char	*p_src;
	unsigned char	*p_dest;

	if (!dest && !src)
		return (NULL);
	p_src = (unsigned char *)src;
	p_dest = (unsigned char *)dest;
	if (dest < src)
	{
		i = 0;
		while (i < n)
		{
			p_dest[i] = p_src[i];
			i++;
		}
	}
	else
	{
		while (n--)
			p_dest[n] = p_src[n];
	}
	return (dest);
}
