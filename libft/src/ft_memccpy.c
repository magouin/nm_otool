/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: magouin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/25 17:03:41 by magouin           #+#    #+#             */
/*   Updated: 2015/11/27 05:44:29 by magouin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	unsigned char	*curdst;
	unsigned char	*cursrc;
	int				i;

	curdst = (unsigned char *)dst;
	cursrc = (unsigned char *)src;
	i = 0;
	while (i < (int)n)
	{
		*curdst = *cursrc;
		if (*cursrc == (unsigned char)c)
			return (curdst + 1);
		i++;
		curdst++;
		cursrc++;
	}
	return (NULL);
}
