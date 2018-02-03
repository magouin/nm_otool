/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: magouin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/19 17:39:49 by magouin           #+#    #+#             */
/*   Updated: 2016/01/11 17:14:30 by magouin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

char	*ft_strtoupper(char *str)
{
	int c;

	c = 0;
	while (str[c] != '\0')
	{
		str[c] = ft_toupper(str[c]);
		c++;
	}
	return (str);
}

void	b_ft_hh(va_list ap, const char *c, int *x, int *o)
{
	unsigned char	cd;

	if (c[*x] == 'o' || c[*x] == 'u' || c[*x] == 'x' || c[*x] == 'X')
	{
		cd = (unsigned char)va_arg(ap, unsigned int);
		if (c[*x] == 'o')
			(*o) += ft_printf("%o", cd);
		if (c[*x] == 'u')
			(*o) += ft_printf("%u", cd);
		if (c[*x] == 'x')
			(*o) += ft_printf("%x", cd);
		if (c[*x] == 'X')
			(*o) += ft_printf("%X", cd);
	}
	else
	{
		test1(ap, c[*x], x, o);
		(*x)--;
	}
}

void	ft_hh(va_list ap, const char *c, int *x, int *o)
{
	signed char		cr;
	signed char		*cf;

	cf = NULL;
	(*x) += 3;
	if (c[*x] == 'd' || c[*x] == 'i')
	{
		cr = (signed char)va_arg(ap, int);
		(*o) += ft_printf("%d", cr);
	}
	else if (c[*x] == 'n')
	{
		cf = va_arg(ap, signed char*);
		cf = (signed char*)o;
	}
	else
		b_ft_hh(ap, c, x, o);
}

void	ft_h(va_list ap, const char *c, int *x, int *o)
{
	unsigned short int	sn;
	int					cd;

	(*x) += 2;
	if (c[*x] == 'o' || c[*x] == 'u' || c[*x] == 'x' || c[*x] == 'X')
	{
		if (c[*x] == 'o')
		{
			sn = va_arg(ap, unsigned int);
			(*o) += ft_printf("%o", sn);
		}
		else
		{
			cd = va_arg(ap, int);
			if (c[*x] == 'u')
				(*o) += ft_printf("%u", cd);
			else if (c[*x] == 'x')
				(*o) += ft_printf("%x", cd);
			else if (c[*x] == 'X')
				(*o) += ft_printf("%X", cd);
		}
	}
	else
		b_ft_h(ap, c, x, o);
}

int		ft_printf(const char *format, ...)
{
	va_list	ap;
	int		x;
	int		o;
	int		d;

	d = 0;
	o = 0;
	x = 0;
	if (format == NULL)
		return (-1);
	va_start(ap, format);
	while (format[x] != '\0')
	{
		if (format[x] == '%')
		{
			ft_flag(ap, format, &x, &o);
		}
		else
			o += ft_putchar(format[x]);
		x++;
	}
	va_end(ap);
	return (o);
}
