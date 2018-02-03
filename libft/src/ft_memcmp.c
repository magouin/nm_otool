/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: magouin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/24 20:42:19 by magouin           #+#    #+#             */
/*   Updated: 2015/11/28 10:28:54 by magouin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	unsigned char	*str;
	unsigned char	*st;
	int				x;
	size_t			v;

	str = (unsigned char*)s1;
	st = (unsigned char*)s2;
	x = 0;
	v = 0;
	while (n--)
	{
		if (str[x] != st[x])
			return ((int)((unsigned char)str[x] - (unsigned char)st[x]));
		x++;
		v++;
	}
	return (0);
}
