/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_uxp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmoreau <vmoreau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/15 20:09:09 by vmoreau           #+#    #+#             */
/*   Updated: 2020/03/12 23:07:26 by vmoreau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/ft_printf.h"

static void		check_uxp3(t_flags *flg, int size)
{
	if (flg->field <= flg->prec && flg->prec > size)
	{
		flg->field = 0;
		flg->prec = flg->prec - size;
		print_0(flg);
	}
	else if (flg->field > flg->prec && flg->prec >= size)
	{
		if (flg->prec >= size && flg->less == 1)
			flg->field = 0;
		else
			flg->field = flg->field - flg->prec;
		flg->prec = flg->prec - size;
		print_0(flg);
	}
	else if (flg->field > size && flg->prec < flg->field && flg->prec < size)
	{
		flg->field = flg->field - size;
		if (flg->prec < 0 && flg->zero_dot == 1)
			flg->zero = 1;
		flg->prec = 0;
		print_0(flg);
	}
}

static void		check_uxp2(t_flags *flg, unsigned int nbr, int size)
{
	if (flg->field == 0 && flg->prec > size)
	{
		flg->prec = flg->prec - size;
		print_0(flg);
	}
	else if (flg->field > 0 && flg->prec == 0)
	{
		if (flg->field <= size && nbr != 0)
			flg->field = 0;
		else if (flg->field > size && nbr != 0)
			flg->field = flg->field - size;
		else if (flg->field > size && nbr != 0 && flg->prec == 0
					&& flg->dot == 1 && flg->ptr == 1)
			flg->field -= size;
		print_0(flg);
	}
	else
		check_uxp3(flg, size);
}

static void		check_uxp_d2(t_flags *flg, unsigned int nbr, int size)
{
	if (flg->field > size && flg->prec > size)
	{
		flg->field -= flg->prec;
		flg->prec -= size;
		print_0(flg);
	}
	else if (flg->field < size && flg->prec < flg->field)
		flg->field = 0;
	else if (flg->field >= size && flg->prec <= size && nbr > 0)
		flg->field -= size;
	else if (flg->prec_neg == 1)
		flg->field -= size;
}

static void		check_uxp_d1(t_flags *flg, unsigned int nbr, int size)
{
	if (flg->field <= size && flg->prec <= size && nbr > 0)
		flg->field = 0;
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
		check_uxp_d2(flg, nbr, size);
}

void			check_uxp(t_flags *flg, t_struct *st, unsigned int nbr, int sz)
{
	if (flg->prec == 0 && flg->dot == 1 && nbr == 0)
		st->bool = 1;
	if (flg->dash == 1)
	{
		if (flg->dot == 0)
			flg->field -= sz;
		else if (flg->dot == 1)
			check_uxp_d1(flg, nbr, sz);
	}
	else
	{
		if (flg->dot == 0)
		{
			flg->field -= sz;
			print_0(flg);
		}
		else if (flg->dot == 1)
			check_uxp2(flg, nbr, sz);
	}
}
