/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_flags.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmoreau <vmoreau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/14 15:54:46 by vmoreau           #+#    #+#             */
/*   Updated: 2020/01/13 16:06:57 by vmoreau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/ft_printf.h"

static void		check_prec(const char **str, t_flags *flg, t_struct *st)
{
	if (**str >= '0' && **str <= '9')
	{
		flg->prec = ft_atoi(*str);
		while (**str == '0')
			(*str)++;
		if (flg->prec != 0)
			(*str) += find_size_dec(flg->prec);
	}
	else
	{
		flg->prec = va_arg(st->args, int);
		if (flg->prec < 0)
			flg->prec_neg = 1;
		(*str)++;
	}
}

static void		check_field(const char **str, t_flags *flg, t_struct *st)
{
	if (**str >= '0' && **str <= '9')
	{
		flg->field = ft_atoi(*str);
		(*str) += find_size_dec(flg->field);
	}
	else
	{
		flg->field = va_arg(st->args, int);
		if (flg->field < 0)
		{
			flg->field = -flg->field;
			flg->dash = 1;
		}
		(*str)++;
	}
}

static void		check_begin(t_flags *flg, const char **str)
{
	if (**str == '-' || **str == '0')
	{
		if (**str == '-')
			flg->dash = 1;
		else if (**str == '0')
			flg->zero = 1;
		(*str)++;
		check_begin(flg, str);
	}
}

void			check_flags(t_flags *flg, t_struct *st, const char **str)
{
	check_begin(flg, str);
	if (flg->dash == 1)
		flg->zero = 0;
	if ((**str >= '0' && **str <= '9') || **str == '*')
		check_field(str, flg, st);
	else if (**str == '.')
		flg->ptr = 2;
	if (**str == '.')
	{
		flg->dot = 1;
		if (flg->zero == 1)
			flg->zero_dot = 1;
		flg->zero = 0;
		(*str)++;
	}
	if ((**str >= '0' && **str <= '9') || **str == '*')
		check_prec(str, flg, st);
	else if (flg->dot == 1)
		flg->ptr = 1;
}
