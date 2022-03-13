/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_char.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hthomas <hthomas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/29 17:49:15 by hthomas           #+#    #+#             */
/*   Updated: 2021/06/17 14:57:22 by hthomas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_printf.h"

static void	ft_write_n(t_sp *sp, int n, char c)
{
	while (n--)
	{
		write(1, &c, 1);
		sp->len++;
	}
}

char	*ft_char(va_list arg, t_sp *sp, t_f *f)
{
	sp->i = va_arg(arg, int);
	if (f->precision)
		ft_write_n(sp, f->pr - 1, '0');
	if (f->minus)
		write(1, &sp->i, 1);
	if (f->width)
	{
		if (f->zero)
			ft_write_n(sp, f->width - 1, '0');
		else
			ft_write_n(sp, f->width - 1, ' ');
	}
	if (!f->minus)
		write(1, &sp->i, 1);
	sp->len++;
	return (ft_strdup(""));
}
