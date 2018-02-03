/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcat.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: magouin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/24 10:24:18 by magouin           #+#    #+#             */
/*   Updated: 2015/11/27 06:11:49 by magouin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

char	*ft_strncat(char *dest, char *src, size_t n)
{
	int		c;
	size_t	d;
	int		f;

	d = 0;
	c = 0;
	f = 0;
	while (dest[c] != '\0')
		c++;
	while (src[f] != '\0' && n > d)
	{
		dest[c] = src[f];
		c++;
		d++;
		f++;
	}
	dest[c] = '\0';
	return (dest);
}
