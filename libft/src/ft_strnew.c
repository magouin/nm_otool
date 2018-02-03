/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: magouin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/26 15:35:30 by magouin           #+#    #+#             */
/*   Updated: 2015/11/27 07:11:23 by magouin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

char	*ft_strnew(size_t size)
{
	char	*str;
	int		n;

	n = (int)size;
	str = malloc(size);
	if (str == NULL)
		return (NULL);
	while (n < (int)size - 1)
	{
		str[n] = '\0';
		n++;
	}
	return (str);
}
