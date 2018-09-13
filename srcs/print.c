/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: magouin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/29 14:05:47 by magouin           #+#    #+#             */
/*   Updated: 2018/01/29 14:06:07 by magouin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_nm.h>

void	printfllx(unsigned long long nb, int z, char *str)
{
	int					len;
	unsigned long long	tmp;
	char				buff[32];

	ft_memset(buff, '0', 32);
	buff[31] = 0;
	len = 1;
	tmp = nb;
	while ((tmp >>= 4))
		len++;
	while (nb && !(nb >> 60))
		nb <<= 4;
	tmp = len;
	len = z - len < 0 ? 0 : (z - len);
	while (tmp--)
	{
		buff[len] = (char)((nb >> 60) + (nb >> 60 >= 10 ? 'a' - 10 : '0'));
		nb <<= 4;
		len++;
	}
	write(1, buff, len);
	str ? write(1, str, ft_strlen(str)) : 0;
}

void	printfx(uint nb, int z, char *str)
{
	int		len;
	uint	tmp;
	char	buff[32];

	ft_memset(buff, '0', 32);
	buff[31] = 0;
	len = 1;
	tmp = nb;
	while ((tmp >>= 4))
		len++;
	while (nb && !(nb >> 28))
		nb <<= 4;
	tmp = len;
	len = z - len < 0 ? 0 : (z - len);
	while (tmp--)
	{
		buff[len] = (char)((nb >> 28) + (nb >> 28 >= 10 ? 'a' - 10 : '0'));
		nb <<= 4;
		len++;
	}
	write(1, buff, len);
	str ? write(1, str, ft_strlen(str)) : 0;
}