/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: magouin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/26 18:43:29 by magouin           #+#    #+#             */
/*   Updated: 2015/11/29 01:04:30 by magouin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

char	*ft_strtrim(char const *s)
{
	int		x;
	int		y;
	char	*str;

	x = 0;
	y = ft_strlen(s) - 1;
	if (s == NULL)
		return (NULL);
	while (s[x] == ' ' || s[x] == '\t' || s[x] == '\n')
	{
		x++;
	}
	while ((s[y] == ' ' || s[y] == '\t' || s[y] == '\n') && y > x)
	{
		y--;
	}
	str = ft_strsub(s, x, y - x + 1);
	return (str);
}
