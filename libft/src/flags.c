/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flags.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: magouin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/10 12:01:26 by magouin           #+#    #+#             */
/*   Updated: 2016/05/14 18:43:31 by magouin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

void	ft_espace_part_2(va_list ap, const char *format, int *x, int *o)
{
	int		d;

	if (format[*x + 2] == '%')
		(*o) += ft_putstr("%");
	else if (format[*x + 2] == 'd' || format[*x + 2] == 'i')
		(d = va_arg(ap, int)) < 0 ? ((*o) += ft_putstr(ft_itoa(d)))
			: (((*o) += ft_putchar(' ')) && ((*o) += ft_putstr(ft_itoa(d))));
	else if (format[*x + 2] == 'u')
		(*o) += ft_putstr(ft_itoa_u(va_arg(ap, unsigned int)));
	else if (format[*x + 2] == '+')
	{
		(*x)++;
		ft_plus(ap, format, x, o);
		(*x) -= 2;
	}
	else if (format[*x + 2] == 'C')
		(d = va_arg(ap, int)) == 0 ? *o += ft_putchar('\0')
			: ft_unicode(d, o);
	else if (format[*x + 2] == 'c')
		*o += ft_putchar((char)va_arg(ap, int));
	else
		ft_espace_part_1(ap, format, x, o);
	(*x) += 2;
}

void	ft_z(va_list ap, const char *format, int *x, int *o)
{
	(*x) += 2;
	if (format[*x] == 'd' || format[*x] == 'i')
		(*o) += ft_putstr(ft_itoa_long(va_arg(ap, long int)));
	else if (format[*x] == 'o')
	{
		test1(ap, 'O', x, o);
		(*x)--;
	}
	else if (format[*x] == 'x')
		*o += ft_putstr(ft_itoa_base_u_long(
					va_arg(ap, unsigned long int), 16));
	else if (format[*x] == 'X')
		*o += ft_putstr(ft_strtoupper(
					ft_itoa_base_u_long(va_arg(ap, unsigned long int), 16)));
	else
	{
		test1(ap, ft_toupper(format[*x]), x, o);
		(*x)--;
	}
}

void	ft_j(va_list ap, const char *format, int *x, int *o)
{
	(*x) += 2;
	if (format[*x] == 'd' || format[*x] == 'i')
		*o += ft_putstr(ft_itoa_long(va_arg(ap, long int)));
	else if (format[*x] == 'o')
	{
		test1(ap, 'O', x, o);
		(*x)--;
	}
	else if (format[*x] == 'x')
		*o += ft_putstr(ft_itoa_base_u_long(
					va_arg(ap, unsigned long int), 16));
	else if (format[*x] == 'X')
		*o += ft_putstr(ft_strtoupper(
					ft_itoa_base_u_long(va_arg(ap, unsigned long int), 16)));
	else
	{
		test1(ap, ft_toupper(format[*x]), x, o);
		(*x)--;
	}
}

void	ft_flag2(va_list ap, const char *format, int *x, int *o)
{
	if (format[*x + 1] == '+')
		ft_plus(ap, format, x, o);
	else if (format[*x + 1] == 'z')
		ft_z(ap, format, x, o);
	else if (format[*x + 1] == '#')
		test2(ap, format, x, o);
	else if (format[*x + 1] == 'l')
		l(ap, format, x, o);
	else if (format[*x + 1] == 'h' && format[*x + 2] == 'h')
		ft_hh(ap, format, x, o);
	else if (format[*x + 1] == 'j')
		ft_j(ap, format, x, o);
	else if (format[*x + 1] == ' ')
		ft_espace_part_2(ap, format, x, o);
	else if (format[*x + 1] == 'h')
		ft_h(ap, format, x, o);
	else if (format[*x + 1] != '\0')
		test1(ap, format[*x + 1], x, o);
}

void	ft_flag(va_list ap, const char *format, int *x, int *o)
{
	int					d;
	int					rez;
	int					chiffre;

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
	else if ((format[*x + 1] <= '9' && format[*x + 1] > '0')
			|| (ft_atoi(format + *x + 1) == 0 && format[*x + 1] == '0'))
		ft_chiffre(ap, format, x, o);
	else if (format[*x + 1] == '0')
		ft_zero(ap, format, x, o);
	else
		ft_flag2(ap, format, x, o);
}
