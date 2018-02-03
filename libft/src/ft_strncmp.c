/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: magouin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/24 14:51:45 by magouin           #+#    #+#             */
/*   Updated: 2015/11/27 06:29:43 by magouin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

int		ft_strncmp(const char *s1, const char *s2, size_t n)
{
	int		c;
	size_t	d;

	c = 0;
	d = 0;
	while (s1[c] != '\0' && d < n && s2[c] != '\0')
	{
		if (s1[c] - s2[c] != 0)
			return ((int)((unsigned char)s1[c] - (unsigned char)s2[c]));
		c++;
		d++;
	}
	if (d == n)
		return ((int)((unsigned char)s1[c - 1] - (unsigned char)s2[c - 1]));
	return ((int)((unsigned char)s1[c] - (unsigned char)s2[c]));
}
