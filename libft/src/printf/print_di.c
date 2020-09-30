/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_di.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmoreau <vmoreau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/14 21:14:25 by vmoreau           #+#    #+#             */
/*   Updated: 2020/01/13 21:17:41 by vmoreau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/ft_printf.h"

static int		check_negative2(int nbr, t_struct *st, t_flags *flg, int *size)
{
	if (flg->field == 0 && flg->prec == -1 && flg->dash == 0)
		st->bool = 5;
	if (flg->dot == 1 && flg->zero == 0)
	{
		(*size)--;
		if (flg->prec_neg == 1 && flg->ptr != 2)
			flg->field--;
		st->nb_read++;
	}
	flg->less = 1;
	if (!(flg->less == 1 && flg->field > flg->prec &&
			flg->dash == 0 && flg->dot == 1))
		if (st->bool != 5)
			ft_putchar('-');
	return (-nbr);
}

static int		check_negative(int nbr, t_struct *st, t_flags *flg, int *size)
{
	if (nbr == -2147483648)
	{
		ft_putchar('-');
		st->min_int = 1;
		(*size)--;
		st->nb_read++;
		return (147483648);
	}
	else if (nbr < 0 && (flg->prec >= *size || flg->zero == 1 ||
				flg->prec_neg == 1))
		return (check_negative2(nbr, st, flg, size));
	else
		return (nbr);
}

void			print_di(t_struct *st, t_flags *flg, const char **str)
{
	int		nbr;
	int		size;

	(*str)++;
	nbr = va_arg(st->args, int);
	size = find_size_dec(nbr);
	nbr = check_negative(nbr, st, flg, &size);
	st->nb_read += set_ret_di(flg, nbr, size);
	check_di(flg, st, nbr, size);
	if (st->min_int == 1)
		ft_putchar('2');
	if (st->bool == 0)
		ft_putnbr(nbr);
	if (flg->dash == 1)
		print_field_d1(flg, st, size, 0);
}
