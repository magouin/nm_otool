/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: magouin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/25 16:05:03 by magouin           #+#    #+#             */
/*   Updated: 2016/01/18 17:24:20 by magouin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

int		ft_calc(int n, int *len)
{
	int k;

	k = n;
	if (n < 0)
	{
		len[1] = 1;
		n *= -1;
	}
	while (k)
	{
		k /= 10;
		len[0]++;
	}
	return (n);
}

void	fln(char *str, int *len)
{
	if (len[1])
		str[0] = '-';
	str[len[0] + len[1]] = '\0';
}

char	*jedoismlloc(int n)
{
	char *st;

	if (n == 0)
	{
		st = malloc(2);
		st[1] = '\0';
		st[0] = '0';
	}
	else
	{
		st = malloc(sizeof(char) * 12);
		st[0] = '-';
		st[1] = '2';
		st[2] = '1';
		st[3] = '4';
		st[4] = '7';
		st[5] = '4';
		st[6] = '8';
		st[7] = '3';
		st[8] = '6';
		st[9] = '4';
		st[10] = '8';
		st[11] = '\0';
	}
	return (st);
}

char	*ft_itoa(int n)
{
	int		len[2];
	char	*str;

	len[0] = 0;
	len[1] = 0;
	if (n == 0 || n == -2147483648)
	{
		str = jedoismlloc(n);
		return (str);
	}
	n = ft_calc(n, len);
	if (!(str = malloc(len[0] * sizeof(char) + 1 + len[1])))
		return (NULL);
	fln(str, len);
	while (n)
	{
		str[len[0] - 1 + len[1]] = n % 10 + '0';
		n /= 10;
		len[0]--;
	}
	return (str);
}
