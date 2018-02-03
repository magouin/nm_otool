/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: magouin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/23 21:08:51 by magouin           #+#    #+#             */
/*   Updated: 2015/11/27 05:54:48 by magouin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

char	*ft_strdup(const char *s)
{
	int		i;
	int		x;
	char	*copie;

	x = 0;
	i = ft_strlen(s);
	if ((copie = malloc(sizeof(char) * (i + 1))) == NULL)
		return (0);
	while (x != i)
	{
		copie[x] = s[x];
		x++;
	}
	copie[x] = '\0';
	return (copie);
}
