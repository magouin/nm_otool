/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: magouin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/19 17:27:22 by magouin           #+#    #+#             */
/*   Updated: 2016/05/14 18:41:06 by magouin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include "libft.h"

int				ft_printf(const char *format, ...);
void			l(va_list ap, const char *c, int *x, int *o);
char			*ft_strtoupper(char *str);
void			ft_unicode(int c, int *o);
void			ft_putbin(int c);
void			ft_putunicode(int *str, int *o);
void			test1(va_list ap, char c, int *x, int *o);
void			test2(va_list ap, const char *c, int *x, int *o);
void			ft_h(va_list ap, const char *c, int *x, int *o);
void			ft_hh(va_list ap, const char *c, int *x, int *o);
void			ft_plus(va_list ap, const char *c, int *x, int *o);
void			ft_flag(va_list ap, const char *format, int *x, int *o);
void			b_ft_h(va_list ap, const char *c, int *x, int *o);
void			ft_chiffre(va_list ap, const char *format, int *x, int *o);
void			ft_zero(va_list ap, const char *format, int *x, int *o);

typedef struct	s_point
{
	int			*x;
	int			*o;
}				t_point;

void			ft_zero1(va_list ap, const char *format, t_point a, int len0);
void			ft_espace_part_1(va_list ap,
		const char *format, int *x, int *o);
#endif
