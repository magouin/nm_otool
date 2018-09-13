/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   converse.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: magouin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/21 14:03:55 by magouin           #+#    #+#             */
/*   Updated: 2016/01/11 16:18:08 by magouin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

void	ft_unicode(int c, int *o)
{
	char c1[4];

	ft_bzero(c1, 4);
	(c == 0) ? (*o)++ && ft_putchar('\0') : 0;
	if (c < 0x80)
		c1[0] = ((c >> 0 & 0x7F) | 0x00);
	else if (c < 0x800)
	{
		c1[0] = ((c >> 6 & 0x1F) | 0xC0);
		c1[1] = ((c >> 0 & 0x3F) | 0x80);
	}
	else if (c < 0x010000)
	{
		c1[0] = ((c >> 12 & 0x0F) | 0xE0);
		c1[1] = ((c >> 6 & 0x3F) | 0x80);
		c1[2] = ((c >> 0 & 0x3F) | 0x80);
	}
	else if (c < 0x110000)
	{
		c1[0] = ((c >> 18 & 0x07) | 0xF0);
		c1[1] = ((c >> 12 & 0x3F) | 0x80);
		c1[2] = ((c >> 6 & 0x3F) | 0x80);
		c1[3] = ((c >> 0 & 0x3F) | 0x80);
	}
	(*o) += ft_putstr(c1);
}

void	ft_putbin(int c)
{
	unsigned int flag;

	flag = 0b10000000000000000000000000000000;
	write(1, "0b", 2);
	while (flag)
	{
		write(1, (flag & c) ? "1" : "0", 1);
		flag >>= 1;
	}
	write(1, "\n", 1);
}

void	ft_putunicode(int *str, int *o)
{
	int x;

	x = 0;
	while (str[x])
	{
		ft_unicode(str[x], o);
		x++;
	}
}

void	l(va_list ap, const char *c, int *x, int *o)
{
	long int *nb;

	(*x) += 2;
	if (c[*x] == 'l')
		(*x)++;
	if (c[*x] == 'p')
	{
		test2(ap, c, x, o);
		(*x)--;
	}
	else if (c[*x] == 'n')
	{
		nb = va_arg(ap, long int*);
		nb = (long int*)o;
	}
	else if (c[*x] == 'x')
		*o += ft_putstr(ft_itoa_base_u_long(va_arg(ap, unsigned long long), 16));
	else if (c[*x] == 'X')
		*o += ft_putstr(ft_strtoupper(
					ft_itoa_base_u_long(va_arg(ap, unsigned long int), 16)));
	else
	{
		test1(ap, ft_toupper(c[*x]), x, o);
		(*x)--;
	}
}
