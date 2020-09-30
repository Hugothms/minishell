/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmoreau <vmoreau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/13 11:08:21 by vmoreau           #+#    #+#             */
/*   Updated: 2019/12/06 17:59:53 by vmoreau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/libft.h"

static int		countword(char const *s, char c)
{
	int count;
	int i;

	i = 0;
	count = 0;
	while (s[i] != '\0')
	{
		if (s[i] == c)
			i++;
		else
		{
			while (s[i] != '\0' && s[i] != c)
				i++;
			count++;
		}
	}
	return (count);
}

static void		ft_free_split(char ***tab, size_t index)
{
	size_t i;

	i = 0;
	if (index > 0)
		index--;
	while (i < index)
	{
		free((*tab)[i]);
		i++;
	}
	free(*tab);
	*tab = NULL;
}

static char		*ft_strncpy(char *dst, const char *src, size_t len)
{
	size_t j;

	j = 0;
	while (src[j] != '\0' && j < len)
	{
		dst[j] = src[j];
		j++;
	}
	dst[j] = '\0';
	while (j < len)
	{
		dst[j] = '\0';
		j++;
	}
	return (dst);
}

static void		ft_splity(char const *s, char c, char ***tab)
{
	size_t i;
	size_t j;
	size_t index;

	i = 0;
	index = 0;
	while (s[i] != '\0')
	{
		if (s[i] == c)
			i++;
		else
		{
			j = 0;
			while (s[i + j] != '\0' && s[i + j] != c)
				j++;
			if (!((*tab)[index] = (char *)malloc(sizeof(char) * (j + 1))))
			{
				ft_free_split(tab, index);
				break ;
			}
			(*tab)[index] = ft_strncpy((*tab)[index], s + i, j);
			index++;
			i = i + j;
		}
	}
}

char			**ft_split(char const *s, char c)
{
	size_t	len;
	char	**tab;

	tab = NULL;
	if (s != NULL)
	{
		len = countword(s, c);
		tab = (char **)malloc(sizeof(char *) * (len + 1));
		if (tab != NULL)
		{
			tab[len] = NULL;
			ft_splity(s, c, &tab);
		}
	}
	return (tab);
}
