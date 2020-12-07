/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hthomas <hthomas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/22 16:16:36 by vmoreau           #+#    #+#             */
/*   Updated: 2020/12/07 19:05:39 by hthomas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int			have_equal(char *str)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '=')
			if (i == 0)
				return (1);
			else
				return (i);
		i++;
	}
	return (0);
}

void		add_quote(char **tri)
{
	int		i;
	int		j;

	i = 0;
	while (tri[i])
	{
		if (have_equal(tri[i]))
		{
			j = ft_strlen(tri[i]) - 2;
			while (j > have_equal(tri[i]))
			{
				tri[i][j] = tri[i][j - 1];
				j--;
			}
			tri[i][j + 1] = '\"';
		}
		i++;
	}
}

static int	ft_strcmp_ex(const char *s1, const char *s2)
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

void		sort(char **tri)
{
	char	*tmp;
	int		i;
	int		j;

	i = 0;
	j = 1;
	if (tri[i])
	{
		while (tri[i + 1] != NULL)
		{
			if (ft_strcmp_ex(tri[i], tri[j]) > 0)
			{
				tmp = tri[j];
				tri[j] = tri[i];
				tri[i] = tmp;
				j = i;
			}
			else if (tri[j + 1] == NULL)
			{
				i++;
				j = i;
			}
			j++;
		}
	}
}

void		print_exp_err(char **key, char **value)
{
	g_glob.exit = 1;
	ft_putstr_fd("minishell: export: « ", STDERR);
	if (*key[0] == '\0' && *value[0])
	{
		ft_putstr_fd(*key, STDERR);
		ft_putstr_fd("=", STDERR);
		ft_putstr_fd(*value, STDERR);
		ft_putstr_fd(" » : not valid identifier\n", STDERR);
	}
	else
	{
		ft_putstr_fd(*key, STDERR);
		ft_putstr_fd(" » : not valid identifier\n", STDERR);
	}
	free(*key);
	free(*value);
}
