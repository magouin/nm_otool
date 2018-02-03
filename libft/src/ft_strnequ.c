/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnequ.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: magouin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/26 17:20:02 by magouin           #+#    #+#             */
/*   Updated: 2015/11/28 12:56:51 by magouin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

int	ft_strnequ(char const *s1, char const *s2, size_t n)
{
	size_t x;

	x = 0;
	if (!s1 || !s2)
		return (0);
	while (s1[x] == s2[x] && s1[x] != '\0' && x < n)
	{
		if (x == n)
			return (1);
		x++;
	}
	if (s1[x] == '\0' || s2[x] == '\0' || x >= n)
		return (1);
	return (0);
}
