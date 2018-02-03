/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: magouin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/26 16:42:54 by magouin           #+#    #+#             */
/*   Updated: 2015/11/27 07:12:41 by magouin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

char	*ft_strmap(char const *s, char (*f)(char))
{
	char	*str;
	int		n;

	str = malloc(sizeof(char) * ft_strlen(s));
	if (str == NULL)
		return (NULL);
	n = 0;
	while (s[n] != '\0')
	{
		str[n] = f(s[n]);
		n++;
	}
	return (str);
}
