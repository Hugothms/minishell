/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_u.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmoreau <vmoreau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/14 21:18:43 by vmoreau           #+#    #+#             */
/*   Updated: 2020/01/10 17:10:12 by vmoreau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/ft_printf.h"

static void		ft_putnbr_u(unsigned int n)
{
	if (n >= 10)
		ft_putnbr(n / 10);
	ft_putchar((n % 10) + '0');
}

void			print_u(t_struct *st, t_flags *flg, const char **str)
{
	int		nbr;
	int		size;

	(void)flg;
	(*str)++;
	nbr = va_arg(st->args, unsigned int);
	size = find_size_dec_u(nbr);
	st->nb_read += set_ret(flg, nbr, size);
	check_uxp(flg, st, nbr, size);
	if (st->bool == 0)
		ft_putnbr_u(nbr);
	if (flg->dash == 1)
		print_field_d1(flg, st, size, 0);
}
