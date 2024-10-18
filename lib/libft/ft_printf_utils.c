/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wacista <wacista@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 18:13:52 by wacista           #+#    #+#             */
/*   Updated: 2024/10/18 18:54:49 by wacista          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_putchar(unsigned char c)
{
	write(2, &c, 1);
}

int	ft_putstr(char *s)
{
	int	len;

	if (!s)
		s = "(null)";
	len = 0;
	while (s[len])
		ft_putchar(s[len++]);
	return (len);
}

int	ft_putnbr(int n)
{
	long	nb;
	int		len;

	nb = n;
	len = 0;
	if (nb < 0)
	{
		ft_putchar('-');
		len++;
		nb *= -1;
	}
	if (nb > 9)
	{
		len += ft_putnbr(nb / 10);
		ft_putchar(nb % 10 + '0');
		len++;
	}
	else
	{
		ft_putchar(nb + '0');
		len++;
	}
	return (len);
}

int	ft_putnbr_unsigned(unsigned int n)
{
	long	nb;
	int		len;

	nb = n;
	len = 0;
	if (nb > 9)
	{
		len += ft_putnbr_unsigned(nb / 10);
		ft_putchar(nb % 10 + '0');
		len++;
	}
	else
	{
		ft_putchar(nb + '0');
		len++;
	}
	return (len);
}

int	ft_putnbr_hex(unsigned long n, char *base)
{
	int		len;

	len = 0;
	if (n >= 16)
	{
		len += ft_putnbr_hex(n / 16, base);
		ft_putchar(base[n % 16]);
		len++;
	}
	else
	{
		ft_putchar(base[n]);
		len++;
	}
	return (len);
}
