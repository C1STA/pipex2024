/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wacista <wacista@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 16:19:21 by wacista           #+#    #+#             */
/*   Updated: 2024/10/18 18:57:06 by wacista          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <unistd.h>
# include <stdarg.h>

int		ft_printf(const char *s, ...);
int		ft_putnbr(int n);
int		ft_putnbr_unsigned(unsigned int n);
void	ft_putchar(unsigned char c);
int		ft_putstr(char *s);
int		ft_putnbr_hex(unsigned long n, char *base);

#endif