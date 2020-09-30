/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmoreau <vmoreau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/06 17:42:21 by vmoreau           #+#    #+#             */
/*   Updated: 2019/12/06 17:59:53 by vmoreau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*sub;
	size_t	i;

	i = 0;
	sub = NULL;
	sub = (char *)malloc(sizeof(char) * (len + 1));
	if (s == NULL || sub == NULL)
		return (NULL);
	if (start > ft_strlen(s) || len == 0)
		sub[0] = '\0';
	else
	{
		while (s[start] != '\0' && i < len)
		{
			sub[i] = s[start];
			i++;
			start++;
		}
		sub[i] = '\0';
	}
	return (sub);
}
