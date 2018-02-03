/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memalloc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: magouin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/26 15:23:04 by magouin           #+#    #+#             */
/*   Updated: 2015/11/27 05:43:26 by magouin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

void	*ft_memalloc(size_t size)
{
	char	*str;
	int		n;
	int		v;

	str = malloc(size);
	if (str == NULL)
		return (NULL);
	n = (int)size;
	v = 0;
	while (v < n)
	{
		str[v] = '\0';
		v++;
	}
	return ((void*)str);
}
