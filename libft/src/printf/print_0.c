/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_0.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmoreau <vmoreau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/09 16:22:56 by vmoreau           #+#    #+#             */
/*   Updated: 2020/01/13 21:09:22 by vmoreau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/ft_printf.h"

void		print_field_d1(t_flags *flg, t_struct *st, int size, int bool)
{
	if (bool == 1)
	{
		if (st->min_int == 1 && flg->prec <= size && flg->prec_neg == 0)
			flg->field -= flg->prec;
		else if (st->min_int == 1 && flg->prec >= size)
			flg->field -= size;
		while (flg->field > 0)
		{
			ft_putchar(' ');
			flg->field--;
		}
	}
	else
	{
		while (flg->field > 0)
		{
			ft_putchar(' ');
			flg->field--;
		}
	}
}

void		print_0s(t_flags *flg)
{
	if (flg->zero == 0 && flg->dash == 0)
	{
		while (flg->field > 0)
		{
			ft_putchar(' ');
			flg->field--;
		}
	}
	else if (flg->zero == 1)
	{
		while (flg->field > 0)
		{
			ft_putchar('0');
			flg->field--;
		}
	}
}

static void	print_0d(t_flags *flg)
{
	if (flg->less2 == 1)
		ft_putchar('-');
	while (flg->field > 0)
	{
		ft_putchar('0');
		flg->field--;
	}
}

void		print_0(t_flags *flg)
{
	if (flg->zero == 0)
	{
		if (flg->dash == 0)
		{
			while (flg->field > 0)
			{
				ft_putchar(' ');
				flg->field--;
			}
		}
		if (flg->less2 == 1)
			ft_putchar('-');
		while (flg->prec > 0)
		{
			ft_putchar('0');
			flg->prec--;
		}
	}
	else if (flg->zero == 1)
		print_0d(flg);
}
