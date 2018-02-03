/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: magouin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/23 23:23:01 by magouin           #+#    #+#             */
/*   Updated: 2015/11/25 21:13:33 by magouin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

char	*ft_strncpy(char *dest, const char *src, size_t n)
{
	size_t	c;
	int		d;

	c = 0;
	d = 0;
	while (src[d] != '\0' && c < n)
	{
		dest[d] = src[d];
		d++;
		c++;
	}
	if (src[d] == '\0')
	{
		while (c < n)
		{
			dest[d] = '\0';
			d++;
			c++;
		}
	}
	return (dest);
}
