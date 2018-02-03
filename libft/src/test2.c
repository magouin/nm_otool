/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: magouin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/10 14:13:35 by magouin           #+#    #+#             */
/*   Updated: 2016/01/11 16:25:22 by magouin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

void	b_test2(va_list ap, const char *c, int *x, int *o)
{
	char	*str;

	if (c[*x + 2] == 'x')
	{
		str = ft_itoa_base_u(va_arg(ap, unsigned int), 16);
		if (str[0] != '0')
			*o += ft_putstr("0x");
		*o += ft_putstr(str);
	}
	else if (c[*x + 2] == 'X')
	{
		str = ft_itoa_base_u(va_arg(ap, unsigned int), 16);
		if (str[0] != '0')
			*o += ft_putstr("0X");
		*o += ft_putstr(ft_strtoupper(str));
	}
	else
	{
		test1(ap, c[*x + 2], x + 1, o);
		(*x)--;
	}
}

void	test2(va_list ap, const char *c, int *x, int *o)
{
	unsigned long int	p;
	char				*str;

	if (c[*x + 2] == 'o' || c[*x + 2] == 'O')
	{
		str = ft_itoa_base_u_long(va_arg(ap, unsigned long int), 8);
		if (str[0] != '0')
			*o += ft_putchar('0');
		*o += ft_putstr(str);
	}
	else if (c[*x + 2] == 'p')
	{
		p = (unsigned long)va_arg(ap, void*);
		*o += ft_putstr("0x");
		*o += ft_putstr(ft_itoa_base_u_long(p, 16));
		(*x)--;
	}
	else
		b_test2(ap, c, x, o);
	(*x) += 2;
}

void	ft_espace_part_1(va_list ap, const char *format, int *x, int *o)
{
	char	*str;
	int		*n;

	if (format[*x + 2] == 's')
	{
		str = va_arg(ap, char*);
		str == NULL ? *o += ft_putstr("(null)") : (*o += ft_putstr(str));
	}
	else if (format[*x + 2] == 'S')
		(n = va_arg(ap, int*)) == NULL ?
			*o += ft_putstr("(null)") : ft_putunicode(n, o);
	else if (format[*x + 2] <= '9' && format[*x + 2] >= '0')
	{
		(*x)++;
		(*o) += ft_putstr(" ");
		ft_flag(ap, format, x, o);
		(*x) -= 2;
	}
	else
	{
		test1(ap, format[*x + 2], x, o);
		(*x)--;
	}
}
