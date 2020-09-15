/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hthomas <hthomas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/18 15:47:39 by hthomas           #+#    #+#             */
/*   Updated: 2020/09/16 00:54:27 by hthomas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*recurs(int depth, int *ret)
{
	char	buff[1];
	char	*out;
	int		test;
	test = read(0, buff, 1);
	if (test == 0)
		buff[0] = 0;
	if (buff[0] == '\n' || buff[0] == 0)
	{
		if (!(out = malloc(sizeof(char) * depth + 1)))
			return (0);
		out[depth] = 0;
		*ret = 1;
		if (buff[0] == 0)
			*ret = 0;
		return (out);
	}
	else
	{
		if (!(out = recurs(depth + 1, ret)))
			return (0);
		out[depth] = buff[0];
	}
	return (out);
}
int		get_next_line_custom(char **out)
{
	int ret;
	ret = 1;
	*out = recurs(0, &ret);
	return (ret);
}
