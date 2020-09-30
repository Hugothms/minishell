/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmoreau <vmoreau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/14 15:26:47 by vmoreau           #+#    #+#             */
/*   Updated: 2020/03/03 12:29:58 by vmoreau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdarg.h>
# include "libft.h"
# define HEXA_LOW "0123456789abcdef"
# define HEXA_UP "0123456789ABCDEF"

/*
** Struct
*/
typedef struct	s_struct
{
	va_list args;
	int		nb_read;
	int		min_int;
	int		read;
	int		bool;
}				t_struct;
typedef struct	s_flags
{
	int		field;
	int		prec;
	int		prec_neg;
	int		dash;
	int		zero;
	int		zero_dot;
	int		dot;
	int		less;
	int		less2;
	int		ptr;
}				t_flags;

/*
** Prototype
*/
int				ft_printf(const char *str, ...);
void			check_flags(t_flags *flg, t_struct *st, const char **str);
void			init_struct(t_flags *flg, t_struct *st);
int				find_size_dec(int nbr);
int				find_size_dec_u(unsigned int nbr);
int				find_size_hex(unsigned int nbr);
int				find_size_hex_ul(unsigned long nbr);
char			*itoa_hex_ul(unsigned long nbr, int i, char *base);
char			*itoa_hex(unsigned int nbr, int i, char *base);
void			check_di(t_flags *flg, t_struct *st, int nbr, int size);
void			check_di_d1(t_flags *flg, int nbr, int size);
void			check_uxp(t_flags *flg, t_struct *st, unsigned int nbr, int sz);
void			check_s(t_flags *flg, t_struct *st, int size);
void			check_cper(t_flags *flg, int size);
void			print_s(t_struct *st, t_flags *flg, const char **str);
void			print_di(t_struct *st, t_flags *flg, const char **str);
void			print_c(t_struct *st, t_flags *flg, const char **str);
void			print_p(t_struct *st, t_flags *flg, const char **str);
void			print_u(t_struct *st, t_flags *flg, const char **str);
void			print_x(t_struct *st, t_flags *flg, const char **str);
void			print_field_d1(t_flags *flg, t_struct *st, int size, int bool);
void			print_0(t_flags *flg);
void			print_0s(t_flags *flg);
int				set_ret(t_flags *flg, int nbr, int size);
int				set_ret_di(t_flags *flg, int nbr, int size);
int				set_ret_s(t_flags *flg, int size);
int				set_ret_c(t_flags *flg, int size);
int				set_ret_p(t_flags *flg, int nbr, int size);
#endif
