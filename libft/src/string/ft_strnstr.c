/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmoreau <vmoreau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/05 12:44:12 by vmoreau           #+#    #+#             */
/*   Updated: 2019/12/06 17:59:53 by vmoreau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/libft.h"

static int	ft_checkneed(char *hay, const char *need, size_t a, size_t b)
{
	int i;
	int bool;

	i = 0;
	bool = 1;
	while (need[i] != '\0' && b + i <= a)
	{
		if (hay[i] != need[i])
		{
			bool = 0;
			break ;
		}
		i++;
	}
	if (need[i] != '\0')
		bool = 0;
	return (bool);
}

char		*ft_strnstr(const char *hay, const char *need, size_t len)
{
	size_t i;

	i = 0;
	if (need[0] == '\0')
		return ((char*)hay);
	while (hay[i] != '\0' && i <= len - 1)
	{
		if (hay[i] == need[0]
			&& ft_checkneed((char*)hay + i, need, len, i) == 1)
			return ((char*)hay + i);
		i++;
	}
	if (need[0] == '\0')
		return ((char*)hay);
	return (NULL);
}
