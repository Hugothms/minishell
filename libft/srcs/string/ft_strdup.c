/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmoreau <vmoreau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/04 16:04:54 by hthomas           #+#    #+#             */
/*   Updated: 2020/11/18 16:29:26 by vmoreau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

char	*ft_strdup(char const *src)
{
	int		len;
	char	*cpy;

	if (src)
	{
		len = ft_strlen(src);
		if (!(cpy = malloc((len + 1) * sizeof(char))))
			return (0);
		ft_memcpy(cpy, src, len);
		cpy[len] = '\0';
		return (cpy);
	}
	return (NULL);
}
