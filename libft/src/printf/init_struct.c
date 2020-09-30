/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_struct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmoreau <vmoreau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/14 16:03:16 by vmoreau           #+#    #+#             */
/*   Updated: 2020/01/09 22:52:34 by vmoreau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/ft_printf.h"

void	init_struct(t_flags *flg, t_struct *st)
{
	flg->field = 0;
	flg->prec = 0;
	flg->prec_neg = 0;
	flg->dash = 0;
	flg->zero = 0;
	flg->zero_dot = 0;
	flg->dot = 0;
	flg->less = 0;
	flg->less2 = 0;
	flg->ptr = 0;
	st->min_int = 0;
	st->read = 0;
	st->bool = 0;
}
