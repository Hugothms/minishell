/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmoreau <vmoreau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/22 16:16:36 by vmoreau           #+#    #+#             */
/*   Updated: 2020/10/27 15:55:25 by vmoreau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int		have_egual(char *str)
{
	int i;
	int ret;

	i = 0;
	ret = 0;
	while (str[i])
	{
		if (str[i] == '=')
			ret = 1;
		i++;
	}
	return (ret);
}

void	add_quote(char **tri)
{
	int		i;
	int		j;

	i = 0;
	while (tri[i])
	{
		if (have_egual(tri[i]))
		{
			j = ft_strlen(tri[i]) - 2;
			while (tri[i][j] != '=')
			{
				tri[i][j] = tri[i][j - 1];
				j--;
			}
			tri[i][j + 1] = '\"';
		}
		i++;
	}
}

int		ft_strcmp_ex(const char *s1, const char *s2)
{
	unsigned int	i;

	i = 0;
	if (s1 == s2)
		return (0);
	while (s1[i] != '=' && s2[i] != '=' && s1[i] == s2[i])
		i++;
	if (s1[i] == '=')
		return (-(unsigned char)s2[i]);
	else if (s2[i] == '=')
		return (-(unsigned char)s1[i]);
	else
		return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

void	sort(char **tri)
{
	char	*tmp;
	int		i;
	int		j;

	i = 0;
	j = 1;
	while (tri[i + 1] != NULL)
	{
		if (ft_strcmp_ex(tri[i], tri[j]) > 0)
		{
			tmp = tri[j];
			tri[j] = tri[i];
			tri[i] = tmp;
			j = i + 1;
		}
		else if (tri[j + 1] == NULL)
		{
			i++;
			j = i + 1;
		}
		else
			j++;
	}
}
