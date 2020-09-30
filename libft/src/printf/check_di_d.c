/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_di_d.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmoreau <vmoreau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/16 00:21:31 by vmoreau           #+#    #+#             */
/*   Updated: 2020/01/10 17:17:01 by vmoreau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/ft_printf.h"

static void		check_di_d3(t_flags *flg, int size)
{
	if (flg->field <= size && flg->prec < size)
		flg->field = 0;
	else if (flg->field > size && flg->prec < size)
		flg->field -= size;
	else if (flg->field > size && flg->prec >= size && flg->prec <= flg->field)
	{
		flg->field -= flg->prec;
		if (flg->less == 1)
			flg->field--;
		flg->prec -= size;
		print_0(flg);
	}
	else if (flg->field > size && flg->prec >= size && flg->prec > flg->field)
	{
		flg->field = 0;
		flg->prec -= size;
		print_0(flg);
	}
	else if (flg->field <= size && flg->prec >= size)
	{
		flg->field = 0;
		flg->prec -= size;
		print_0(flg);
	}
}

static void		check_di_d2(t_flags *flg, int nbr, int size)
{
	if (flg->field > size && flg->prec > size)
	{
		flg->field -= flg->prec;
		flg->prec -= size;
		print_0(flg);
	}
	else if (flg->field < size && flg->prec < size)
		flg->field = 0;
	else if (flg->field >= size && flg->prec <= size && nbr > 0)
		flg->field -= size;
	else if (flg->field > size && flg->prec < 0 && nbr == 0)
		flg->field -= size;
	else if (flg->field >= size && flg->prec < 0 && nbr == 0
			&& flg->prec_neg == 1)
		flg->field -= size;
}

void			check_di_d1(t_flags *flg, int nbr, int size)
{
	if (nbr >= 0 && flg->less == 0)
	{
		if (flg->field <= size && flg->prec >= size)
		{
			flg->field = 0;
			if (flg->prec > size)
			{
				flg->prec -= size;
				print_0(flg);
			}
		}
		else if (flg->field > size && flg->prec > 0 && flg->prec <= size)
			flg->field -= size;
		else
			check_di_d2(flg, nbr, size);
	}
	else if (nbr < 0 || flg->less == 1)
		check_di_d3(flg, size);
}
