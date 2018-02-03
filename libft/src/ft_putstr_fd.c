/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: magouin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/24 18:58:36 by magouin           #+#    #+#             */
/*   Updated: 2016/05/14 18:43:01 by magouin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

void	ft_putstr_fd(int fd, ...)
{
	int		i;
	char	*str;
	va_list	ap;

	va_start(ap, fd);
	str = va_arg(ap, char*);
	while (str != NULL)
	{
		i = 0;
		while (str[i] != '\0')
		{
			write(fd, &(str[i]), 1);
			i++;
		}
		str = va_arg(ap, char*);
	}
	va_end(ap);
	exit(EXIT_FAILURE);
}
