/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: magouin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/26 17:30:12 by magouin           #+#    #+#             */
/*   Updated: 2015/11/28 21:56:58 by magouin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

char	*ft_strsub(char const *s, unsigned int start, size_t len)
{
	char	*str;
	size_t	n;

	n = 0;
	str = malloc(sizeof(char) * len + 1);
	if (str == NULL)
		return (str);
	if (start >= ft_strlen(s))
	{
		str[0] = '\0';
		return (str);
	}
	if (!s)
		return (str);
	while (n < len)
	{
		str[n] = s[start + n];
		n++;
	}
	str[len] = '\0';
	return (str);
}
