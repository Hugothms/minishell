/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_size.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmoreau <vmoreau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/14 19:06:21 by vmoreau           #+#    #+#             */
/*   Updated: 2020/03/12 22:35:05 by vmoreau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/ft_printf.h"

int		find_size_dec(int nbr)
{
	int size;

	size = 0;
	if (nbr == 0)
		return (1);
	if (nbr < 0)
		size++;
	while (nbr > 0 || nbr < 0)
	{
		nbr = nbr / 10;
		size++;
	}
	return (size);
}

int		find_size_dec_u(unsigned int nbr)
{
	int size;

	size = 0;
	if (nbr == 0)
		return (1);
	while (nbr > 0)
	{
		nbr = nbr / 10;
		size++;
	}
	return (size);
}

int		find_size_hex(unsigned int nbr)
{
	int size;

	size = 0;
	if (nbr == 0)
		return (1);
	while (nbr > 0)
	{
		nbr = nbr / 16;
		size++;
	}
	return (size);
}

int		find_size_hex_ul(unsigned long nbr)
{
	int size;

	size = 0;
	if (nbr == 0)
		return (1);
	while (nbr > 0)
	{
		nbr = nbr / 16;
		size++;
	}
	return (size);
}
