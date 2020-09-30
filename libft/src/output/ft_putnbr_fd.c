/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmoreau <vmoreau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/07 15:20:58 by vmoreau           #+#    #+#             */
/*   Updated: 2019/12/06 17:59:53 by vmoreau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	long n1;

	n1 = (long)n;
	if (n1 < 0)
	{
		ft_putchar_fd('-', fd);
		n1 = n1 * -1;
	}
	if (n1 >= 10)
		ft_putnbr_fd(n1 / 10, fd);
	ft_putchar_fd((n1 % 10) + '0', fd);
}
