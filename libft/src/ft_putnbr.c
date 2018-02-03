/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: magouin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/27 02:10:01 by magouin           #+#    #+#             */
/*   Updated: 2015/11/29 00:59:00 by magouin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

void	thelse(int n, int k)
{
	if (n < 0)
	{
		n *= -1;
		ft_putchar('-');
	}
	while (n / k == 0)
		k /= 10;
	if (n < 10)
		ft_putchar(n + '0');
	else
	{
		while (k != 1)
		{
			ft_putchar((n / k) + '0');
			n = n - (n / k) * k;
			k /= 10;
			if (k == 1)
				ft_putchar(n + '0');
		}
	}
}

void	ft_putnbr(int n)
{
	int k;

	k = 1000000000;
	if (n == -2147483648)
		ft_putstr("-2147483648");
	else if (n == 0)
		ft_putchar('0');
	else
		thelse(n, k);
}
