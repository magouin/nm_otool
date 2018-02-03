/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_chiffre.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: magouin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/12 09:42:18 by magouin           #+#    #+#             */
/*   Updated: 2016/05/14 18:42:31 by magouin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

void	ft_chiffre1(va_list ap, const char *format, t_point a, int len0)
{
	unsigned long int	nbul;
	int					lennb;

	lennb = 0;
	if (format[*(a.x)] == 'p' || format[*(a.x)] == 'x')
	{
		nbul = va_arg(ap, long unsigned int);
		lennb = ft_strlen(ft_itoa_u_long(nbul));
		while (len0 > (lennb + 2))
		{
			(*(a.o)) += ft_putchar(' ');
			lennb++;
		}
		(*(a.o)) += ft_putstr("0x");
		(*(a.o)) += ft_putstr(ft_itoa_base_u_long(nbul, 16));
	}
	else
	{
		while (len0 > lennb + 1)
		{
			(*(a.o)) += ft_putchar(' ');
			lennb++;
		}
		(*(a.x))--;
	}
}

void	ft_chiffre2(va_list ap, const char *format, t_point a, int len0)
{
	unsigned long int	nbul;
	int					lennb;
	char				*t;

	lennb = 0;
	if (format[*(a.x)] == 'U')
	{
		nbul = va_arg(ap, long unsigned int);
		lennb = ft_strlen(ft_itoa_u_long(nbul)) - 1;
		while (len0 > ++lennb)
			(*(a.o)) += ft_putchar(' ');
		*(a.o) += ft_putstr(ft_itoa_u_long(nbul));
	}
	else if (format[*(a.x)] == 's')
	{
		t = va_arg(ap, char*);
		lennb = ft_strlen(t) - 1;
		while (len0 > ++lennb)
			(*(a.o)) += ft_putchar(' ');
		*(a.o) += ft_putstr(t);
	}
	else
		ft_chiffre1(ap, format, a, len0);
}

void	ft_chiffre3(va_list ap, const char *format, t_point a, int len0)
{
	int					lennb;
	int					nbu;
	long int			nbl;

	if (format[*(a.x)] == 'u')
	{
		nbu = va_arg(ap, unsigned int);
		lennb = ft_strlen(ft_itoa_u(nbu)) - 1;
		while (len0 > ++lennb)
			(*(a.o)) += ft_putchar(' ');
		*(a.o) += ft_putstr(ft_itoa_u(nbu));
	}
	else if (format[*(a.x)] == 'D' || format[*(a.x)] == 'I')
	{
		nbl = va_arg(ap, long int);
		lennb = ft_strlen(ft_itoa_long(nbl)) - 1;
		len0++;
		while (len0 > ++lennb)
			(*(a.o)) += ft_putchar(' ');
		*(a.o) += ft_putstr(ft_itoa_long(nbl));
	}
	else
		ft_chiffre2(ap, format, a, len0);
}

void	ft_chiffre4(va_list ap, const char *format, t_point a, int len0)
{
	int					*n;
	int					k;
	int					lennb;

	lennb = 0;
	k = -1;
	if (format[*(a.x)] == 'S')
	{
		n = va_arg(ap, int*);
		while (n[++k] != 0)
		{
			lennb += 2;
			(n[k] > 256) ? lennb += 1 : 0;
			(n[k] > (256 * 256)) ? lennb += 1 : 0;
			(n[k] > (256 * 256 * 256)) ? (lennb += 1) : 0;
		}
		while (len0 > lennb)
		{
			(*(a.o)) += ft_putchar(' ');
			lennb++;
		}
		n == NULL ? *(a.o) += ft_putstr("(null)") : ft_putunicode(n, (a.o));
	}
	else
		ft_chiffre3(ap, format, a, len0);
}

void	ft_chiffre(va_list ap, const char *format, int *x, int *o)
{
	int					nb;
	int					len0;
	int					lennb;
	t_point				a;

	a.x = x;
	a.o = o;
	(format[*x] == ' ' || format[*x] == '+') ? (len0 = ft_atoi(
		format + *x + 1) - 1) : (len0 = ft_atoi(format + *x + 1));
	(*x) += (ft_strlen(ft_itoa(len0)) + 1);
	if (format[*x] == 'd' || format[*x] == 'i' || format[*x] == 'c')
	{
		nb = va_arg(ap, int);
		if (format[*x] != 'c')
			lennb = ft_strlen(ft_itoa(nb)) - 1;
		else
			(lennb = 0);
		while (len0 > ++lennb)
			(*o) += ft_putchar(' ');
		(format[*x] != 'c') ? (*o += ft_putstr(ft_itoa(nb)))
			: (*o += ft_putchar((char)nb));
	}
	else
		ft_chiffre4(ap, format, a, len0);
}
