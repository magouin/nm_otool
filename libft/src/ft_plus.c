/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_plus.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: magouin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/10 14:15:04 by magouin           #+#    #+#             */
/*   Updated: 2016/01/11 16:58:17 by magouin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

void	bb_ft_plus(va_list ap, const char *c, int *x, int *o)
{
	int tmp;

	if (c[*x + 2] == ' ')
	{
		(*x)++;
		ft_plus(ap, c, x, o);
		(*x) -= 2;
	}
	else if (c[*x + 2] <= '9' && c[*x + 2] >= '0')
	{
		tmp = *x;
		*o += ft_putstr("+");
		(*x)++;
		ft_flag(ap, c, x, o);
		(*x) -= 2;
	}
	else
	{
		test1(ap, c[*x + 2], x, o);
		(*x)--;
	}
}

void	b_ft_plus(va_list ap, const char *c, int *x, int *o)
{
	if (c[*x + 2] == 'U')
		*o += ft_putstr(ft_itoa_u_long(va_arg(ap, unsigned long int)));
	else if (c[*x + 2] == 'o' || c[*x + 2] == 'O')
		*o += ft_putstr(ft_itoa_base_u_long(va_arg(ap, unsigned long int), 8));
	else if (c[*x + 2] == 'x' || c[*x + 2] == 'p')
		*o += ft_putstr(ft_itoa_base_u(va_arg(ap, unsigned int), 16));
	else if (c[*x + 2] == 'X')
		*o += ft_putstr(ft_strtoupper(
					ft_itoa_base_u(va_arg(ap, unsigned long), 16)));
	else if (c[*x + 2] == 'c')
		*o += ft_putchar((char)va_arg(ap, int));
	else if (c[*x + 2] == 'u')
		*o += ft_putstr(ft_itoa_u(va_arg(ap, int)));
	else
		bb_ft_plus(ap, c, x, o);
}

void	ft_plus(va_list ap, const char *c, int *x, int *o)
{
	int					d;
	unsigned long int	p;

	if (c[*x + 2] == 'd' || c[*x + 2] == 'i')
	{
		d = va_arg(ap, int);
		d < 0 ? (*o += ft_putstr(ft_itoa(d)))
			: ((*o += ft_putstr("+")) && (*o += ft_putstr(ft_itoa(d))));
	}
	else if (c[*x + 2] == 'D' || c[*x + 2] == 'I')
	{
		d = va_arg(ap, int);
		d < 0 ? (*o += ft_putstr(ft_itoa_long(d)))
			: ((*o += ft_putstr("+")) && (*o += ft_putstr(ft_itoa_long(d))));
	}
	else if (c[*x + 2] == 'p')
	{
		p = (unsigned long)va_arg(ap, void*);
		*o += ft_putstr("0x");
		*o += ft_putstr(ft_itoa_base_u_long(p, 16));
	}
	else
		b_ft_plus(ap, c, x, o);
	(*x) += 2;
}
