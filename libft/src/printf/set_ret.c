/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_ret.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmoreau <vmoreau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/15 00:53:51 by vmoreau           #+#    #+#             */
/*   Updated: 2020/01/10 16:33:50 by vmoreau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/ft_printf.h"

int		set_ret_di(t_flags *flg, int nbr, int size)
{
	if (flg->prec == 0 && nbr == 0 && flg->dot == 1 && flg->field == 0)
		return (0);
	else if (flg->field > flg->prec && flg->prec > size && flg->less == 1)
		return (flg->field - 1);
	else if (flg->field > flg->prec && flg->prec >= size && flg->less == 1)
		return (flg->prec);
	else if (flg->field > size && flg->prec <= flg->field)
		return (flg->field);
	else if (flg->field > size && flg->prec > flg->field)
		return (flg->prec);
	else if (flg->field < flg->prec && flg->prec > size)
		return (flg->prec);
	else
		return (size);
}

int		set_ret_p(t_flags *flg, int nbr, int size)
{
	if (flg->prec == 0 && nbr == 0 && flg->dot == 1 && flg->field == 0)
		return (2);
	if (flg->field > flg->prec && flg->prec >= size && flg->less == 1)
		return (flg->prec);
	else if (flg->field > size && flg->prec <= flg->field)
		return (flg->field);
	else if (flg->field > size && flg->prec > flg->field)
		return (flg->prec);
	else if (flg->field < flg->prec && flg->prec > size)
		return (flg->prec);
	else
		return (size);
}

int		set_ret(t_flags *flg, int nbr, int size)
{
	if (flg->prec == 0 && nbr == 0 && flg->dot == 1 && flg->field == 0)
		return (0);
	if (flg->field > flg->prec && flg->prec >= size && flg->less == 1)
		return (flg->prec);
	else if (flg->field > size && flg->prec <= flg->field)
		return (flg->field);
	else if (flg->field > size && flg->prec > flg->field)
		return (flg->prec);
	else if (flg->field < flg->prec && flg->prec > size)
		return (flg->prec);
	else
		return (size);
}

int		set_ret_c(t_flags *flg, int size)
{
	if (flg->field > size)
		return (flg->field);
	else
		return (1);
}

int		set_ret_s(t_flags *flg, int size)
{
	if (flg->prec < 0 && -flg->prec >= size)
		flg->prec = size;
	if (flg->field > size && flg->prec <= flg->field)
		return (flg->field);
	else if (flg->field > size && size == 0)
		return (flg->field);
	else if (flg->field > size && flg->prec > flg->field)
		return (flg->field);
	else if (flg->dot == 1 && flg->prec == 0 && flg->field == 0)
		return (0);
	else if (flg->dot == 1 && flg->prec == 0 && flg->field > 0)
		return (flg->field);
	else if (flg->prec < size && flg->prec > flg->field)
		return (flg->prec);
	else if (flg->field < size && flg->dot == 0 && flg->dash == 1)
		return (size);
	else if (flg->field < size && flg->dot == 0)
		return (size);
	else if (flg->field < size && flg->prec < flg->field && flg->prec > 0)
		return (flg->field);
	else if (flg->field < size && flg->prec < size && flg->field <= flg->prec)
		return (flg->prec);
	else
		return (size);
}
