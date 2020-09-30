/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmoreau <vmoreau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/06 19:17:15 by vmoreau           #+#    #+#             */
/*   Updated: 2019/12/06 17:59:53 by vmoreau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/libft.h"

static int	ft_checkdec(int n)
{
	int i;

	i = 1;
	if (n < 0)
		i++;
	while (n >= 10 || n <= -10)
	{
		n = n / 10;
		i++;
	}
	return (i);
}

char		*ft_itoa(int n)
{
	char	*str;
	int		k;
	long	n1;

	n1 = (long)n;
	k = ft_checkdec(n);
	str = malloc(sizeof(char) * (k + 1));
	if (str == NULL)
		return (NULL);
	if (n1 < 0)
	{
		n1 = n1 * -1;
		str[0] = '-';
	}
	str[k] = '\0';
	k--;
	if (n1 == 0)
		str[k] = '0';
	while (n1 > 0)
	{
		str[k] = '0' + (n1 % 10);
		n1 = n1 / 10;
		k--;
	}
	return (str);
}
