/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dup.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: magouin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/04 10:51:07 by magouin           #+#    #+#             */
/*   Updated: 2018/02/04 10:51:08 by magouin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_nm.h>

int64_t			r_int64(int64_t data)
{
	int64_t tmp;

	tmp = (data & 0xff) << 0x38;
	tmp |= (data & 0xff00) << 0x28;
	tmp |= (data & 0xff0000) << 0x18;
	tmp |= (data & 0xff000000) << 0x8;
	tmp |= (data & 0xff00000000) >> 0x8;
	tmp |= (data & 0xff0000000000) >> 0x18;
	tmp |= (data & 0xff000000000000) >> 0x28;
	tmp |= (data & 0xff00000000000000) >> 0x38;
	return (tmp);
}

int				r_int32(int data)
{
	int tmp;

	tmp = (data & 0xff) << 0x18;
	tmp |= (data & 0xff00) << 0x8;
	tmp |= (data & 0xff0000) >> 0x8;
	tmp |= (data & 0xff000000) >> 0x18;
	return (tmp);
}
