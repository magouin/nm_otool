/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: magouin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/26 23:21:05 by magouin           #+#    #+#             */
/*   Updated: 2016/04/19 15:57:47 by magouin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

void	creationdutab(char const *s, char c, int *dim)
{
	int n;
	int compte;

	n = -1;
	dim[1] = 0;
	dim[0] = 0;
	compte = 0;
	while (s[++n] == c)
		compte++;
	while (s[n] != '\0')
	{
		while (s[n] != c && s[n] != '\0')
		{
			compte++;
			if (compte > dim[1])
				dim[1] = compte;
			n++;
		}
		dim[0]++;
		while (s[n] == c)
			n++;
		compte = 0;
	}
}

void	final(char const *s, char c, char **str)
{
	int n;
	int x;
	int y;

	x = -1;
	y = -1;
	n = -1;
	while (s[++n] == c)
		str[y + 1][++x] = c;
	while (s[n] != '\0')
	{
		if (s[n] != c)
		{
			while (s[n] != c && s[n] != '\0')
			{
				str[y + 1][++x] = s[n];
				n++;
			}
			str[++y][++x] = '\0';
			x = -1;
		}
		else
			n++;
	}
	str[y + 1] = NULL;
}

char	**ft_strsplit(char const *s, char c)
{
	int		dim[2];
	char	**str;
	int		mots;

	if (s == NULL)
		return (NULL);
	creationdutab(s, c, dim);
	mots = 0;
	str = (char**)malloc(sizeof(char*) * (dim[0] + 1));
	if (str == NULL)
		return (NULL);
	while (mots < dim[0])
	{
		str[mots] = (char*)malloc(sizeof(char) * (dim[1] + 1));
		if (str[mots] == NULL)
			return (NULL);
		mots++;
	}
	final(s, c, str);
	return (str);
}
