/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_chiffre.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: magouin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/12 09:39:31 by magouin           #+#    #+#             */
/*   Updated: 2016/01/25 16:12:55 by magouin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

void	ft_zero2(va_list ap, const char *format, t_point a, int len0)
{
	int					lennb;
	char				*t;
	unsigned long int	nbul;

	if (format[*(a.x) + 1] == 's')
	{
		t = va_arg(ap, char*);
		lennb = ft_strlen(t);
		while (len0 > lennb)
		{
			(*(a.o)) += ft_putchar('0');
			lennb++;
		}
		*(a.o) += ft_putstr(t);
	}
	else if (format[*(a.x) + 1] == 'U')
	{
		nbul = va_arg(ap, long unsigned int);
		lennb = ft_strlen(ft_itoa_u_long(nbul)) + 1;
		while (len0 > ++lennb)
			(*(a.o)) += ft_putchar('0');
		*(a.o) += ft_putstr(ft_itoa_u_long(nbul));
	}
	else
		ft_zero1(ap, format, a, len0);
}

void	ft_zero3(va_list ap, const char *format, t_point a, int len0)
{
	unsigned int		nbu;
	int					lennb;
	long int			nbl;

	if (format[*(a.x) + 1] == 'u')
	{
		nbu = va_arg(ap, unsigned int);
		lennb = ft_strlen(ft_itoa_u(nbu)) - 1;
		while (len0 > ++lennb)
			(*(a.o)) += ft_putchar('0');
		*(a.o) += ft_putstr(ft_itoa_u(nbu));
	}
	else if (format[*(a.x) + 1] == 'D' || format[*(a.x) + 1] == 'I')
	{
		nbl = va_arg(ap, long int);
		lennb = ft_strlen(ft_itoa(nbl)) - 1;
		(nbl < 0) ? (*(a.o)) += ft_putchar('-') & (nbl *= -1) : 0;
		while (len0 > ++lennb)
			(*(a.o)) += ft_putchar('0');
		*(a.o) += ft_putstr(ft_itoa(nbl));
	}
	else
		ft_zero2(ap, format, a, len0);
}

void	ft_zero4(va_list ap, const char *format, t_point a, int len0)
{
	int					lennb;
	int					*n;
	int					k;

	k = -1;
	lennb = -1;
	if (format[*(a.x) + 1] == 'S')
	{
		n = va_arg(ap, int*);
		while (n[++k] != 0)
		{
			if (n[k] < 256)
				lennb += 2;
			else if (n[k] < (256 * 256))
				lennb += 3;
			else if (n[k] < (256 * 256 * 256))
				lennb += 4;
			(n[k] >= (256 * 256 * 256)) ? lennb += 5 : 0;
		}
		while (len0 > ++lennb)
			(*(a.o)) += ft_putchar('0');
		n == NULL ? *(a.o) += ft_putstr("(null)") : ft_putunicode(n, a.o);
	}
	else
		ft_zero3(ap, format, a, len0);
}

void	ft_zero5(va_list ap, const char *format, t_point a, int len0)
{
	long int			nb;
	int					lennb;

	(format[*(a.x)] == ' ') || (format[*(a.x)] == '+') ? (len0 = ft_atoi(
	format + *(a.x) + 1) - 1) : (len0 = ft_atoi(format + *(a.x) + 1));
	(*(a.x)) += (ft_strlen(ft_itoa(len0)) + 1);
	if (format[*(a.x) + 1] == 'd' || format[*(a.x) + 1] == 'i'
			|| format[*(a.x) + 1] == 'c')
	{
		nb = va_arg(ap, int);
		format[*(a.x) + 1] != 'c' ? lennb = ft_strlen(ft_itoa(nb)) - 1
					: (lennb = 0);
		if (nb < (long)0)
		{
			(*(a.o)) += ft_putchar('-');
			nb *= -1;
		}
		while (len0 > ++lennb)
			(*(a.o)) += ft_putchar('0');
		(format[*(a.x) + 1] != 'c') ? (*(a.o) += ft_putstr(ft_itoa(nb)))
			: (*(a.o) += ft_putchar((char)nb));
	}
	else
		ft_zero4(ap, format, a, len0);
}

void	ft_zero(va_list ap, const char *format, int *x, int *o)
{
	int					rez;
	int					d;
	int					chiffre;
	t_point				a;

	a.x = x;
	a.o = o;
	d = 0;
	chiffre = 0;
	while (format[*x + 1 + chiffre] <= '9' && format[*x + 1 + chiffre] >= '0')
		chiffre++;
	if (format[*x + 1 + chiffre] == '-')
	{
		(*x) += chiffre;
		rez = *o;
		d = ft_atoi(format + *x + 2);
		(*x) += (ft_strlen(ft_itoa_long(d)) + 1);
		ft_flag(ap, format, x, o);
		while ((*o - rez) < d)
			(*o) += ft_putchar(' ');
	}
	ft_zero5(ap, format, a, 0);
	(*x)++;
}
