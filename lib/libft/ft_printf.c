/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wacista <wacista@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 16:22:42 by wacista           #+#    #+#             */
/*   Updated: 2024/10/18 18:57:30 by wacista          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	is_arg(char c)
{
	char	*s;

	s = "cspdiuxX%";
	while (*s)
	{
		if (*s == c)
			return (1);
		s++;
	}
	return (0);
}

int	ft_putptr(unsigned long n)
{
	int	len;

	if (!n)
		return (ft_putstr("(nil)"));
	len = ft_putstr("0x");
	len += ft_putnbr_hex(n, "0123456789abcdef");
	return (len);
}

int	ft_checkconversions(va_list(args), int len, char c)
{
	if (c == 'c' || c == '%')
	{
		if (c == 'c')
			ft_putchar(va_arg(args, int));
		else
			ft_putchar('%');
		len++;
	}
	else if (c == 'd' || c == 'i')
		len += ft_putnbr(va_arg(args, int));
	else if (c == 's')
		len += ft_putstr(va_arg(args, char *));
	else if (c == 'u')
		len += ft_putnbr_unsigned(va_arg(args, unsigned int));
	else if (c == 'x')
		len += ft_putnbr_hex(va_arg(args, unsigned int), "0123456789abcdef");
	else if (c == 'X')
		len += ft_putnbr_hex(va_arg(args, unsigned int), "0123456789ABCDEF");
	else if (c == 'p')
		len += ft_putptr(va_arg(args, unsigned long));
	return (len);
}

int	ft_printf(const char *s, ...)
{
	int		i;
	int		len;
	va_list	args;

	va_start(args, s);
	i = 0;
	len = 0;
	while (s[i])
	{
		if (s[i] == '%' && is_arg(s[i + 1]))
		{
			len = ft_checkconversions(args, len, s[i + 1]);
			i += 2;
		}
		else
		{
			ft_putchar(s[i]);
			i++;
			len++;
		}
	}
	va_end(args);
	return (len);
}
