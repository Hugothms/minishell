/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_p.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmoreau <vmoreau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/14 21:54:08 by vmoreau           #+#    #+#             */
/*   Updated: 2020/01/10 17:11:43 by vmoreau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/ft_printf.h"

void			print_p(t_struct *st, t_flags *flg, const char **str)
{
	char			*hexabase;
	char			*adr;
	long			nbr;
	int				i;

	hexabase = HEXA_LOW;
	nbr = va_arg(st->args, long);
	(*str)++;
	i = find_size_hex_ul(nbr);
	if (nbr == 0 && flg->prec == 0 && flg->dot == 1)
		i = 0;
	st->nb_read += set_ret_p(flg, nbr, i + 2);
	flg->field -= 2;
	check_uxp(flg, st, nbr, i);
	adr = itoa_hex_ul(nbr, i, hexabase);
	ft_putstr("0x");
	if (!(nbr == 0 && flg->prec == 0 && flg->dot == 1))
		ft_putstr(adr);
	if (flg->dash == 1)
		print_field_d1(flg, st, i, 0);
	free(adr);
}
