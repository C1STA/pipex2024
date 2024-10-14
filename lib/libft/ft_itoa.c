/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wacista <wacista@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 21:21:04 by wacista           #+#    #+#             */
/*   Updated: 2024/05/30 21:27:42 by wacista          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static long	ft_numlen(long nb)
{
	long	size;

	size = 0;
	if (nb == 0)
		size++;
	if (nb < 0)
	{
		nb *= -1;
		size++;
	}
	while (nb > 0)
	{
		nb /= 10;
		size++;
	}
	return (size);
}

char	*ft_itoa(int n)
{
	long	nb;
	long	len;
	char	*s;

	nb = n;
	len = ft_numlen(nb);
	s = (char *)malloc(sizeof(char) * (len + 1));
	if (!s)
		return (NULL);
	s[len] = '\0';
	if (nb == 0)
		*s = '0';
	if (nb < 0)
	{
		*s = '-';
		nb *= -1;
	}
	while (nb > 0)
	{
		s[--len] = nb % 10 + '0';
		nb /= 10;
	}
	return (s);
}
