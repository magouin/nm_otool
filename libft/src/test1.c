/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test1.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: magouin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/10 14:10:38 by magouin           #+#    #+#             */
/*   Updated: 2016/05/14 18:44:22 by magouin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

void	ft_zero1(va_list ap, const char *format, t_point a, int len0)
{
	unsigned long int	nbul;
	int					lennb;

	if (format[*(a.x) + 1] == 'p')
	{
		nbul = va_arg(ap, long unsigned int);
		lennb = ft_strlen(ft_itoa_u_long(nbul));
		*(a.o) += ft_putstr("0x");
		while (len0 > (lennb + 2))
		{
			(*(a.o)) += ft_putchar('0');
			lennb++;
		}
		*(a.o) += ft_putstr(ft_itoa_base_u_long(nbul, 16));
	}
	else if (format[*(a.x) + 1] == 'x' || format[*(a.x) + 1] == 'X')
	{
		nbul = va_arg(ap, long unsigned int);
		lennb = ft_strlen(ft_itoa_base_u_long(nbul, 16)) - 1;
		while (len0 > ++lennb)
			(*(a.o)) += ft_putchar('0');
		format[*(a.x) + 1] == 'x' ? (*(a.o) += ft_putstr(ft_itoa_base_u_long(
			nbul, 16))) : (*(a.o) += ft_putstr(
		ft_strtoupper(ft_itoa_base_u_long(nbul, 16))));
	}
}

void	bb_test1(va_list ap, char c, int *o)
{
	int	cb;
	int	*n;

	if (c == 'u')
		*o += ft_putstr(ft_itoa_u_long(va_arg(ap, unsigned int)));
	else if (c == 'U')
		*o += ft_putstr(ft_itoa_u_long(va_arg(ap, unsigned long int)));
	else if (c == 'X')
		*o += ft_putstr(ft_strtoupper(
					ft_itoa_base_u_long(va_arg(ap, unsigned int), 16)));
	else if (c == 'C')
		(cb = va_arg(ap, int)) == 0 ?
			*o += ft_putchar('\0') : ft_unicode(cb, o);
	else if (c == 'S')
		(n = va_arg(ap, int*)) == NULL ?
			*o += ft_putstr("(null)") : ft_putunicode(n, o);
	else
		*o += ft_putchar(c);
}

void	b_test1(va_list ap, char c, int *o)
{
	unsigned long int	p;

	if (c == 'p')
	{
		p = (unsigned long)va_arg(ap, void*);
		*o += ft_putstr("0x");
		*o += ft_putstr(ft_itoa_base_u_long(p, 16));
	}
	else if (c == 'o' || c == 'O')
	{
		if (c == 'o')
			*o += ft_putstr(ft_itoa_base_u(va_arg(ap, unsigned int), 8));
		else
			*o += ft_putstr(ft_itoa_base_u_long(
						va_arg(ap, unsigned long int), 8));
	}
	else if (c == 'x')
		*o += ft_putstr(ft_itoa_base_u_long(va_arg(ap, unsigned int), 16));
	else
		bb_test1(ap, c, o);
}

void	test1(va_list ap, char c, int *x, int *o)
{
	int					*n;
	char				*str;

	if (c == 'n')
	{
		n = va_arg(ap, int*);
		n = o;
	}
	else if (c == 'D' || c == 'I')
		*o += ft_putstr(ft_itoa_long(va_arg(ap, long int)));
	else if (c == 'd' || c == 'i')
		*o += ft_putstr(ft_itoa_long(va_arg(ap, int)));
	else if (c == 's')
	{
		str = va_arg(ap, char*);
		str == NULL ? *o += ft_putstr("(null)") : (*o += ft_putstr(str));
	}
	else if (c == 'c')
		*o += ft_putchar((char)va_arg(ap, int));
	else if (c == '%')
		*o += ft_putchar('%');
	else
		b_test1(ap, c, o);
	(*x)++;
}

void	b_ft_h(va_list ap, const char *c, int *x, int *o)
{
	short	*n;

	if (c[*x] == 'n')
	{
		n = (short*)va_arg(ap, int*);
		*n = (short)*o;
	}
	else if (c[*x] == 'd' || c[*x] == 'i')
		*o += ft_putstr(ft_itoa((short int)va_arg(ap, int)));
	else
	{
		test1(ap, c[*x], x, o);
		(*x)--;
	}
}
