/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmoreau <vmoreau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/14 15:29:27 by vmoreau           #+#    #+#             */
/*   Updated: 2019/12/15 01:42:25 by vmoreau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/ft_printf.h"

static void		check_after_persent(const char **str, t_struct *st)
{
	t_flags flg;

	init_struct(&flg, st);
	check_flags(&flg, st, str);
	if (**str == 'c' || **str == '%')
		print_c(st, &flg, str);
	else if (**str == 's')
		print_s(st, &flg, str);
	else if (**str == 'd' || **str == 'i')
		print_di(st, &flg, str);
	else if (**str == 'p')
		print_p(st, &flg, str);
	else if (**str == 'u')
		print_u(st, &flg, str);
	else if (**str == 'x' || **str == 'X')
		print_x(st, &flg, str);
}

int				ft_printf(const char *str, ...)
{
	t_struct st;

	st.nb_read = 0;
	va_start(st.args, str);
	while (*str != '\0')
	{
		if (*str == '%')
		{
			str++;
			check_after_persent(&str, &st);
		}
		else
		{
			ft_putchar(*str);
			str++;
			st.nb_read++;
		}
	}
	va_end(st.args);
	return (st.nb_read);
}
