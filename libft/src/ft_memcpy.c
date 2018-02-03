/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: magouin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/25 17:02:48 by magouin           #+#    #+#             */
/*   Updated: 2015/11/29 14:22:46 by magouin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	unsigned char	*cur1;
	unsigned char	*curdent;
	int				i;

	i = 0;
	while (i < (int)n)
	{
		cur1 = (unsigned char *)dst + i;
		curdent = (unsigned char *)src + i;
		*cur1 = *curdent;
		i++;
	}
	return (dst);
}
