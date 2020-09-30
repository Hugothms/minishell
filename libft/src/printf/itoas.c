/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   itoa.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmoreau <vmoreau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/14 23:29:07 by vmoreau           #+#    #+#             */
/*   Updated: 2019/12/14 23:31:55 by vmoreau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/ft_printf.h"

char	*itoa_hex_ul(unsigned long nbr, int i, char *base)
{
	char *ret;

	if (!(ret = (char *)malloc(sizeof(char) * (i + 1))))
		return (NULL);
	ret[i--] = '\0';
	while (nbr > 0 || i >= 0)
	{
		ret[i--] = base[(nbr % 16)];
		nbr /= 16;
	}
	return (ret);
}

char	*itoa_hex(unsigned int nbr, int i, char *base)
{
	char *ret;

	if (!(ret = (char *)malloc(sizeof(char) * (i + 1))))
		return (NULL);
	ret[i--] = '\0';
	while (nbr > 0 || i >= 0)
	{
		ret[i--] = base[(nbr % 16)];
		nbr /= 16;
	}
	return (ret);
}
